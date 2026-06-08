#include "map.h"

Map::Map(std::string nome) : Grafo() {
    nome_ = nome;
    descricao_ = "";
}

Map::Map(std::string nome, Grafo grafo) : Grafo(grafo) {
    nome_ = nome;
    descricao_ = "";
}

Map::Map(std::string nome, Grafo grafo, std::unordered_map<long long, LugarMap> lugares) : Grafo(grafo) {
    nome_ = nome;
    descricao_ = "";
    dict_estruturas_ = lugares;
}

Map::~Map() {}

const std::unordered_map<long long, LugarMap> Map::dict_estruturas() {
    return this->dict_estruturas_;
}


void Map::insere_lugar(long long id, LugarMap lugar) {
    dict_estruturas_[id] = lugar;
}

void Map::remove_lugar(long long id) {
    dict_estruturas_.erase(id);
}

void Map::adiciona_descricao(std::string descricao) {
    descricao_ = descricao;
}

void Map::altera_nome(std::string nome) {
    nome_ = nome;
}

const std::string Map::nome() {
    return nome_;
}

const std::string Map::descricao() {
    return descricao_;
}
