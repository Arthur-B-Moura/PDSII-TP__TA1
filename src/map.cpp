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

std::string Map::nome() {
    return nome_;
}

std::string Map::descricao() {
    return descricao_;
}
