#include "map.h"

Map::Map() : Grafo() {
    nome_ = "";
    descricao_ = "";
}

Map::Map(Grafo grafo) : Grafo(grafo) {
    nome_ = "";
    descricao_ = "";
}

Map::Map(Grafo grafo, std::unordered_map<long long, LugarMap> lugares) : Grafo(grafo) {
    nome_ = "";
    descricao_ = "";
    dict_estruturas_ = lugares;
}

Map::~Map() {}

void Map::insere_lugar(long long id, LugarMap lugar) {
    dict_estruturas_[id] = lugar;
}

void Map::remove_lugar(long long id) {
    dict_estruturas_.erase(id);
}

std::string Map::nome() {
    return nome_;
}

std::string Map::descricao() {
    return descricao_;
}
