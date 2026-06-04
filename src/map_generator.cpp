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


class MapGenSaxParser : public xmlpp::SaxParser {
    private:
        int state_ = STATE_IDLE;

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
                state_ = STATE_WAY;
            }
            else if (name == "node") {
                state_ = STATE_NODE;
            }
            else {
                if (state_ != STATE_WAY)
                    state_ = STATE_IDLE;
            }
        }

    public:
        MapGenSaxParser() : xmlpp::SaxParser() {}
        virtual ~MapGenSaxParser() {}
    
    protected:
        void on_start_element(const Glib::ustring& name, 
                              const AttributeList& attributes) override {

            update_state(name);
            if (state_ != STATE_WAY) return;

            std::cout << "Start element: " << name << std::endl;
            for (const auto& attr : attributes) {
                if (useful_attribute(attr.name)) {
                    std::cout << "  Attribute: " << attr.name << " = " << attr.value << std::endl;
                }
            }
        }

        void on_end_element(const Glib::ustring& name) override {
            if (name == "way" && state_ == STATE_WAY) {
                update_state("idle");
            }
        }
        
        void on_error(const Glib::ustring& message) override {
            std::cerr << "Error: " << message << std::endl;
        }

        void on_warning(const Glib::ustring& message) override {
            std::cerr << "Warning: " << message << std::endl;
        }
};



void temp_build_from_osm(const std::string& path) {
    try {
        MapGenSaxParser parser;
        parser.parse_file(path); 
    }
    catch(const xmlpp::exception& ex) {
        std::cerr << "libxml++ exception: " << ex.what() << std::endl;
    }
}


MapGenerator::MapGenerator(std::string path_to_file) {
    // TODO: validar path_to_file
    this->filename_ = path_to_file;

    // TODO: check file type
    // TODO: add osm check
    // this->mapa_ = this->build_from_osm();
    temp_build_from_osm(path_to_file);
}

// Map MapGenerator::build_from_json() {
// }

// Map MapGenerator::build_from_osm() {
//     try {
//         MapGenSaxParser parser;
//         parser.parse_file(this->filename()); 
//     }
//     catch(const xmlpp::exception& ex) {
//         std::cerr << "libxml++ exception: " << ex.what() << std::endl;
//     }
//     return Map();
// }

const std::string MapGenerator::filename() {
    return this->filename_;
}

// Map MapGenerator::mapa() {
//     return this->mapa_;
// }

MapGenerator::~MapGenerator() {
    // TODO: make sure file is closed
    // TODO: clear memory
}