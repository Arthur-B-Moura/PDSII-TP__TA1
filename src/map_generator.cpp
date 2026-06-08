/**  
 * @file map_generator.cpp
 *
 * @brief Implementação do MapGenerator e do parser SAX interno (MapGenSaxParser)
 * utilizados para construção de objetos Map a partir de arquivos .osm (XML).
 *
 * Dependências externas:
 *   sudo apt update
 *   sudo apt install libxml++2.6-dev
 *
 * TODO: Estudar OSM API para integração futura
 */


#include "map_generator.h"

#include <libxml++/libxml++.h> 
#include <iostream>
#include <locale>
#include <clocale>

#define STATE_IDLE 0
#define STATE_WAY 1
#define STATE_NODE 2


// =============================================================================
// Configuração de Locale
// =============================================================================

/**
 * @brief Configura o locale global para o padrão do sistema na inicialização.
 *
 * Necessário para compatibilidade com libxml++-2.6, que usa UTF-8 por padrão.
 * Sem essa configuração, caracteres acentuados (´, `, ~, ^) causam falha fatal
 * de execução ao serem lidos do arquivo .osm.
 */
struct GlobalLocaleSetter {
    GlobalLocaleSetter() {
        std::locale::global(std::locale(""));
    }
};

/// Instância global — garante que o locale seja configurado antes de qualquer parsing.
static GlobalLocaleSetter global_locale_init; 


// =============================================================================
// Tipos auxiliares internos
// =============================================================================

/**
 * @brief Estrutura temporária para acumulação de dados de um "way" OSM durante
 *        o parsing SAX, antes de sua inserção definitiva no mapa.
 *
 * Um "way" no formato OSM representa uma via (rua, avenida, etc.) composta por
 * uma sequência ordenada de nós. Esta struct armazena os campos relevantes
 *
 */  
struct RuaLugarBuffer {
    long long int id;
    std::string tag;
    std::string nome;
};

// =============================================================================
// Estados do parser SAX
// =============================================================================

/**
 * @brief Estados possíveis do parser durante a leitura do arquivo .osm.
 *
 * O parser SAX é orientado a eventos; o estado atual determina como cada
 * elemento XML encontrado deve ser interpretado.
 */
enum class ParseState {
    IDLE, ///< Nenhum elemento relevante em processamento
    WAY,  ///< Dentro de um elemento <way>
    NODE  ///< Dentro de um elemento <node>
};

// =============================================================================
// MapGenSaxParser — parser SAX interno
// =============================================================================

/**
 * @brief Parser SAX especializado para arquivos .osm (OpenStreetMap XML).
 *
 * Herda de xmlpp::SaxParser e sobrescreve os callbacks de início/fim de
 * elemento para construir um objeto Map incrementalmente durante a leitura.
 *
 * Fluxo geral:
 *  - Elementos <node> → nós do grafo (intersecções com coordenadas)
 *  - Elementos <way>  → arestas entre nós + metadados de lugar (nome, tipo)
 *
 * @note Esta classe é de uso exclusivamente interno ao MapGenerator e não é
 *       exposta pelo cabeçalho público.
 *
 * TODO: Remover auto-conexão de nó ao seu próprio vetor de adjacência
 * TODO: Adicionar atributos adicionais de aresta (tipo de rua, sentido, etc.)
 */
class MapGenSaxParser : public xmlpp::SaxParser {
    
    // -------------------------------------------------------------------------
    // Membros privados
    // -------------------------------------------------------------------------
    private:
        ParseState state_ = ParseState::IDLE;

        // int state_ = STATE_IDLE;

        /// Nós referenciados pelo <way> atual, usados para criação de arestas.
        std::vector<long long int> connected_nodes_ = {};

        /// Buffer de dados do <way> (RuaLugar, Estrutura) em processamento.
        RuaLugarBuffer temp_lugar_;


        // -------------------------------------------------------------------------
        // Helpers de transição de estado
        // -------------------------------------------------------------------------

        /**
         * @brief Atualiza o estado do parser com base no nome do elemento XML aberto.
         * @param name Nome do elemento XML (ex: "way", "node", "tag").
         */
        void update_state(const Glib::ustring& name) {
            if      (name == "way")  state_ = ParseState::WAY;
            else if (name == "node") state_ = ParseState::NODE;
            else if (state_ != ParseState::WAY)
            state_ = ParseState::IDLE;
            // Elementos filhos de <way> (ex: <nd>, <tag>) não resetam o estado WAY
        }

        // -------------------------------------------------------------------------
        // Processamento de <node>
        // -------------------------------------------------------------------------

        /**
         * @brief Lê os atributos de um elemento <node> e insere o nó no mapa.
         *
         * Atributos lidos: id, lat, lon.
         *
         * @param attributes Lista de atributos do elemento <node>.
         */
        void store_node(const AttributeList& attributes) {
            long long int id_;
            Coordenada    coord_;
            
            for (const auto& attr : attributes) {
                if (attr.name == "id")  id_               = std::stoll(attr.value.c_str());
                if (attr.name == "lat") coord_.latitude_  = std::stod(attr.value.c_str());
                if (attr.name == "lon") coord_.longitude_ = std::stod(attr.value.c_str());
            }

            mapa_.add_node(MapNode(id_, coord_));
        }   

        // -------------------------------------------------------------------------
        // Processamento de <way> e seus filhos
        // -------------------------------------------------------------------------
    
        /**
         * @brief Realiza o processamento de sub-elementos de um <way>.
         *
         * Delega para parse_edge_nodes() ou parse_tags_lugar() conforme o elemento.
         *
         * @param name       Nome do elemento filho (ex: "nd", "tag", "way").
         * @param attributes Lista de atributos do elemento.
         */
        void parse_way(const Glib::ustring& name, const AttributeList& attributes) {
            if      (name == "nd")                     parse_edge_nodes(attributes);
            else if (name == "tag" || name == "way")   parse_tags_lugar(attributes);
        }
        
        /**
         * @brief Coleta o atributo "ref" de um elemento <nd>, adicionando o id do
         *        nó referenciado à lista de nós conectados do way atual.
         *
         * @param attributes Lista de atributos do elemento <nd>.
         */
        void parse_edge_nodes(const AttributeList& attributes) {
            for (const auto& attr : attributes) {
                if (attr.name == "ref") {
                    this->connected_nodes_.push_back(std::stoll(attr.value.c_str()));
                    return;
                } 
            }
        }

        /**
         * @brief Extrai metadados relevantes dos elementos <way> e <tag> filhos.
         *
         * Preenche way_buffer_ com id, tipo ("highway" → "Rua") e nome da via.
         * Apenas ways do tipo "highway" são considerados vias relevantes.
         *
         * @param attributes Lista de atributos do elemento <way> ou <tag>.
         */
        void parse_tags_lugar(const AttributeList& attributes) {
            if (attributes.empty()) return;

            // Atributo "id" identifica o início de um novo way
            if (attributes[0].name == "id") {
                temp_lugar_.id = std::stoll(attributes[0].value.c_str());
                return;
            }

            // Atributo "k" indica uma tag OSM chave-valor
            if (attributes[0].name != "k") return;

            if      (attributes[0].value == "highway") temp_lugar_.tag  = "Rua";
            else if (attributes[0].value == "name")    temp_lugar_.nome = attributes[1].value;
        }

        
        // -------------------------------------------------------------------------
        // Persistência ao fim de um <way>
        // -------------------------------------------------------------------------
        
        void store_lugar_way() {
            if (this->temp_lugar_.tag != "Rua") return;

            this->mapa_.insere_lugar(this->temp_lugar_.id, 
                                     LugarMap{
                                        this->temp_lugar_.tag,
                                        this->temp_lugar_.nome,
                                        this->connected_nodes_,
                                        std::vector<long long>(this->connected_nodes_.size(), 0)
                                        }
                                    );
        
            this->temp_lugar_ = RuaLugarBuffer{};                      
        }

        /**
         * @brief Cria arestas no grafo conectando todos os nós referenciados pelo
         *        way atual e limpa o buffer de nós conectados.
         *
         * TODO: Remover a auto-conexão de cada nó ao seu próprio vetor
         */
        void store_edge() {
            for (const auto& id : this->connected_nodes_) {
                this->mapa_.add_edge(id, this->connected_nodes_);
            }
            this->connected_nodes_.clear();
        }
    
    // -------------------------------------------------------------------------
    // Callbacks SAX (interface xmlpp::SaxParser)
    // -------------------------------------------------------------------------
    protected:

        /**
         * @brief Callback invocado ao abrir um elemento XML.
         *
         * Atualiza o estado e delega o processamento conforme o elemento.
         *
         * @param name       Nome do elemento aberto.
         * @param attributes Lista de atributos do elemento.
         */
        void on_start_element(const Glib::ustring& name, const AttributeList& attributes) override {
            update_state(name);

            if (state_ == ParseState::NODE) store_node(attributes);
            if (state_ == ParseState::WAY)  parse_way(name, attributes);
        }

        /**
         * @brief Callback invocado ao fechar um elemento XML.
         *
         * Ao fechar um <way>, persiste os dados acumulados no mapa e reseta o estado.
         *
         * @param name Nome do elemento fechado.
         */
        void on_end_element(const Glib::ustring& name) override {
            if (name == "way" && state_ == ParseState::WAY) {
                store_lugar_way();
                store_edge();
                update_state("idle");
            }
        }
        
        /**
         * @brief Callback de erro do parser SAX.
         * @param message Mensagem de erro reportada pela libxml++.
         */
        void on_error(const Glib::ustring& message) override {
            std::cerr << "[MapGenSaxParser] Erro: " << message << std::endl;
        }

        /**
         * @brief Callback de aviso do parser SAX.
         * @param message Mensagem de aviso reportada pela libxml++.
         */
        void on_warning(const Glib::ustring& message) override {
            std::cerr << "[MapGenSaxParser] Aviso: " << message << std::endl;
        }

    // -------------------------------------------------------------------------
    // Interface pública do parser
    // -------------------------------------------------------------------------
    public:

        /// Mapa construído incrementalmente durante o parsing.
        Map mapa_{"generated_map"};

        MapGenSaxParser() : xmlpp::SaxParser() {}
        virtual ~MapGenSaxParser() {}
};


// =============================================================================
// MapGenerator — implementação
// =============================================================================

/**
 * @brief Constrói o MapGenerator e inicia a leitura do arquivo .osm indicado.
 *
 * @param path_to_file Caminho para o arquivo .osm a ser lido.
 *
 * TODO: Validar existência e permissão de leitura do arquivo
 * TODO: Detectar tipo do arquivo (suporte futuro a .csv e .json)
 */
MapGenerator::MapGenerator(std::string path_to_file)
    : filename_(path_to_file) {
    mapa_ = build_from_osm();
}

/**
 * @brief Executa o parsing SAX do arquivo .osm e retorna o mapa resultante.
 *
 * Em caso de erro, registra a exceção em stderr e retorna um mapa vazio
 * com o nome "empty_map".
 *
 * @return Map construído a partir do arquivo, ou Map("empty_map") em caso de falha.
 */
Map MapGenerator::build_from_osm() {
    try {
        MapGenSaxParser parser;
        parser.parse_file(filename());
        return parser.mapa_;
    }
    catch (const xmlpp::exception& ex) {
        std::cerr << "[MapGenerator] Exceção libxml++: " << ex.what() << std::endl;
    }
    catch (const std::exception& ex) {
        std::cerr << "[MapGenerator] Exceção padrão: "  << ex.what() << std::endl;
    }
    catch (...) {
        std::cerr << "[MapGenerator] Exceção desconhecida durante parsing OSM." << std::endl;
    }
    return Map("empty_map");
}

/**
 * @brief Retorna o caminho do arquivo .osm associado a este gerador.
 * @return Caminho do arquivo como string.
 */
const std::string MapGenerator::filename() {
    return this->filename_;
}

/**
 * @brief Retorna referência ao mapa construído pelo gerador.
 * @return Referência para o objeto Map interno.
 */
Map& MapGenerator::get_mapa(){
    return this->mapa_;
}

/// @brief  Destrutor padrão MapGenerator   
MapGenerator::~MapGenerator() {}