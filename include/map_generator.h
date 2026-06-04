#ifndef MAP_GENERATOR_H__
#define MAP_GENERATOR_H__

#include <string>
#include <fstream>
// #include "map.h"

class MapGenerator {
private:
    // Nome do arquivo de texto onde mapa deverá estar armazenado
    std::string filename_;

    // Objeto mapa construído a partir da leitura do arquivo
    // Map mapa_;

    // Map build_from_osm();

    // Map build_from_json();
public:
    MapGenerator(std::string path_to_file);
    
    ~MapGenerator();

    // Map mapa();

    const std::string filename();
};

#endif