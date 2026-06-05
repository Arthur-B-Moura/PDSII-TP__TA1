/* 
sudo apt update
sudo apt install libxml++2.6-dev 
*/

#define STATE_IDLE 0
#define STATE_WAY 1
#define STATE_NODE 2

#include "map_generator.h"
#include <libxml++/libxml++.h> //TODO: update libxml++ library version to more recent one (5.0 likely). Current is 2.6
#include <iostream>
#include <locale>
#include <clocale>

/* Configura locale global versus default UTF-8 usado com libxml++-2.6 para permitir
leitura de valores com acentos (´,`,~,^) sem ocasionar em uma falha fatal de execução */
struct GlobalLocaleSetter {
    GlobalLocaleSetter() {
        // Set locale global c++ para default do sistema
        std::locale::global(std::locale(""));
    }
};

// Inicialização global de locale
static GlobalLocaleSetter global_locale_init; 

// Sax Parser específico para leitura de arquivos osm xml, para construção de mapas
class MapGenSaxParser : public xmlpp::SaxParser {
    private:
        int state_ = STATE_IDLE;
        // Mapeia nós conectados entre si por um osn::way, permitindo posterior mapeamento em edges
        std::vector<long long int> connected_nodes_ = {};

        bool useful_attribute(const Glib::ustring name) {
            return true;
            if (name == "id" || 
                name == "lat" ||
                name == "lon") 
                return true;
            return false;
        }

        void update_state(const Glib::ustring& name) {
            if (name == "way") {
                state_ = STATE_WAY; }
            else if (name == "node") {
                state_ = STATE_NODE; }
            else {
                if (state_ != STATE_WAY)
                    state_ = STATE_IDLE;
            }
        }

        void store_node(const AttributeList& attributes) {
            long long int id_;
            Coordenada coord_;
            
            for (const auto& attr : attributes) {
                if (attr.name == "id") id_ =  std::stoll(attr.value.c_str());
                if (attr.name == "lat") coord_.latitude_ = std::stod(attr.value.c_str());
                if (attr.name == "lon") coord_.longitude_ = std::stod(attr.value.c_str());
            }
            MapNode node(id_, coord_);
            this->mapa_.add_node(node);
        }   

        void parse_edge_nodes(const AttributeList& attributes) {
            for (const auto& attr : attributes) {
                if (attr.name == "ref") {
                    this->connected_nodes_.push_back(std::stoll(attr.value.c_str()));
                    return;
                } 
            }
        }

        // TODO: remove conexão ao próprio vetor (sempre está sendo criada agora)
        // TODO: adicona outros atributos de edge (ex: tipo de rua, sentido, etc)
        void store_edge() {
            for (const auto& id : this->connected_nodes_) {
                this->mapa_.add_edge(id, this->connected_nodes_);
            }

            this->connected_nodes_.clear();
        }
    
    protected:
        void on_start_element(const Glib::ustring& name, const AttributeList& attributes) override {
            update_state(name);
            if (this->state_ == STATE_NODE) store_node(attributes);
            if (this->state_ == STATE_WAY)  parse_edge_nodes(attributes);
            // std::cout << "Start element: " << name << std::endl;
        }


        void on_end_element(const Glib::ustring& name) override {
            if (name == "way" && state_ == STATE_WAY) {
                update_state("idle");
                store_edge();
            }
        }
        

        void on_error(const Glib::ustring& message) override {
            std::cerr << "Error: " << message << std::endl;
        }


        void on_warning(const Glib::ustring& message) override {
            std::cerr << "Warning: " << message << std::endl;
        }

    public:
        Map mapa_{"generated_map"};
        MapGenSaxParser() : xmlpp::SaxParser() {}
        virtual ~MapGenSaxParser() {}
};

///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

/// @brief 
/// @param path_to_file 
MapGenerator::MapGenerator(std::string path_to_file) {
    // TODO: validar path_to_file
    this->filename_ = path_to_file;

    // TODO: check file type
    // TODO: add osm check
    this->mapa_ = this->build_from_osm();
}

Map MapGenerator::build_from_osm() {
    try {
        MapGenSaxParser parser;
        parser.parse_file(this->filename()); 

        const auto& mapa = parser.mapa_;
        return mapa;
        }
    catch(const xmlpp::exception& ex) {
        std::cerr << "libxml++ exception: " << ex.what() << std::endl;
    }
    catch(const std::exception& ex) {
        std::cerr << "Standard exception: " << ex.what() << std::endl;
    }
    catch(...) {
        std::cerr << "Unknown exception occurred while parsing OSM file." << std::endl;
    }
    return Map("empty_map");
}


const std::string MapGenerator::filename() {
    return this->filename_;
}


Map& MapGenerator::get_mapa(){
    return this->mapa_;
}


MapGenerator::~MapGenerator() {
    // TODO: make sure file is closed
    // TODO: clear memory
}