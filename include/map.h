/**
 * @file    map.h
 * @brief   Declaração das estruturas LugarMap e da classe Map.
 *
 * Define a estrutura LugarMap, que representa unidades espaciais do mapa
 * (lugares, construções, vias), e a classe Map, que estende Grafo com
 * metadados geográficos e um dicionário de estruturas identificadas.
 */

#ifndef MAP_H__
#define MAP_H__

#include "grafo.h"
#include <string>
#include <vector>
#include <unordered_map>

// ============================================================================= //
//                                    LugarMap                                   //
// ============================================================================= //

/**
 * @brief   Representa uma unidade espacial do mapa (lugar, construção ou via).
 *
 * Agrupa os metadados semânticos de um elemento geográfico — como um hospital,
 * parque ou rua — junto com as referências aos nós que definem sua geometria
 * no grafo de navegação.
 */
struct LugarMap {
    /// @brief Tipo do elemento geográfico (ex: "hospital", "parque", "rua").
    std::string tag;

    /// @brief Nome próprio do elemento (ex: "Hospital Santa Casa", "Rua Liberdade").
    std::string nome;

    /// @brief IDs dos nós de cruzamento que delimitam o polígono do objeto.
    std::vector<long long> nodes_id_ref;

    /// @brief Deslocamentos relativos entre nós para posicionamento das arestas do polígono.
    std::vector<long long> nodes_delta_ref;
};

// ======================================================================== //
//                                    Map                                   //
// ======================================================================== //

/**
 * @brief   Mapa geográfico estendido com metadados e dicionário de estruturas.
 *
 * Herda de Grafo e acrescenta:
 *  - nome e descrição textuais do mapa;
 *  - um dicionário de LugarMap indexado por ID, permitindo associar
 *    elementos geográficos semânticos aos nós do grafo.
 */
class Map : public Grafo {
private:
    /// @brief Nome identificador do mapa.
    std::string nome_;

    /// @brief Descrição textual opcional do mapa.
    std::string descricao_;

    /// @brief Dicionário de estruturas geográficas, indexadas por ID.
    std::unordered_map<long long, LugarMap> dict_estruturas_;

public:
    // ------------------------- //
    // Construtores e destrutor  //
    // ------------------------- //
    
    /**
     * @brief   Constrói um Map vazio com apenas um nome.
     * @param   nome  Nome do mapa.
     */
    Map(std::string nome);
    
    /**
     * @brief   Constrói um Map a partir de um Grafo existente.
     * @param   nome   Nome do mapa.
     * @param   grafo  Grafo base a ser incorporado.
     */
    Map(std::string nome, Grafo grafo);
    
    /**
     * @brief   Constrói um Map completo com grafo e estruturas pré-existentes.
     * @param   nome     Nome do mapa.
     * @param   grafo    Grafo base a ser incorporado.
     * @param   lugares  Dicionário inicial de estruturas geográficas.
     */
    Map(std::string nome, Grafo grafo, std::unordered_map<long long, LugarMap> lugares);

    /// @brief Destrutor padrão de Mapa.
    ~Map();

    // --------------------------------------- //
    // Mutadores - modificam o estado do mapa  //
    // --------------------------------------- //
    
    /**
     * @brief   Insere ou substitui uma estrutura geográfica no dicionário.
     * @param   id     ID da estrutura a ser inserida.
     * @param   lugar  Dados da estrutura (LugarMap).
     */
    void insere_lugar(long long id, LugarMap lugar);
    
    /**
     * @brief   Remove uma estrutura geográfica do dicionário pelo ID.
     *
     * Se o ID não existir no dicionário, a operação é ignorada.
     *
     * @param   id  ID da estrutura a ser removida.
     */
    void remove_lugar(long long id);
    
    /**
     * @brief   Define ou substitui a descrição textual do mapa.
     * @param   descricao  Novo texto de descrição.
     */
    void adiciona_descricao(std::string descricao);

    /**
     * @brief   Altera o nome do mapa.
     * 
     * Caso o nome inserido não seja válido, mantém o nome anterior. (TODO: this)
     * 
     * @param   nome  Novo nome.
     */
    void altera_nome(std::string nome);

    // --------------------------------------- //
    // Acessores - leitura do estado do mapa   //
    // --------------------------------------- //

    /**
     * @brief   Retorna o dicionário completo de estruturas geográficas.
     * @return  Cópia do mapa de LugarMap indexado por ID.
     */
    const std::unordered_map<long long, LugarMap> dict_estruturas();
    
    /**
     * @brief   Retorna o nome do mapa.
     * @return  String com o nome atual.
     */
    const std::string nome();

    /**
     * @brief   Retorna a descrição textual do mapa.
     * @return  String com a descrição atual (vazia se não definida).
     */
    const std::string descricao();
};


#endif // MAP_H__
