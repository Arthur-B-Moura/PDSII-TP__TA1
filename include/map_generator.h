#ifndef MAP_GENERATOR_H__
#define MAP_GENERATOR_H__

#include <string>
#include "map.h"

class MapGenerator {
private:
    std::string filename_;
    Map mapa_;

    Map build_from_csv();

    Map build_from_jsom();
    
public:
    MapGenerator(std::string path_to_file);
    
    ~MapGenerator();

    Map map();
};

#endif