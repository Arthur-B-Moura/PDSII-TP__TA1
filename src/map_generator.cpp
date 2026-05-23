#include "map_generator.h"


MapGenerator::MapGenerator(std::string path_to_file) {
    // TODO: validar path_to_file
    this->filename_ = path_to_file;

    // TODO: check file type
    // TODO: add osm check
    this->mapa_ = this->build_from_json();
}

Map MapGenerator::build_from_json() {
}

Map MapGenerator::build_from_osm() {
}

const std::string MapGenerator::filename() {
    return this->filename_;
}

Map MapGenerator::mapa() {
    return this->mapa_;
}

MapGenerator::~MapGenerator() {
    // TODO: make sure file is closed
    // TODO: clear memory
}