#include "map_node.h"

MapNode::MapNode(const long long int id) {
    this->id_ = id;
    this->posicao_ = std::nullopt;
}

// TO-DO: Inserir check coordenada válida
MapNode::MapNode(const long long int id, Coordenada pos) {
    this->id_ = id;
    this->posicao_ = pos;
}

MapNode::~MapNode(){
    this->vizinhos_.clear();
}

std::optional<Coordenada> MapNode::posicao() {
    return this->posicao_;    
}

long long int MapNode::id() {
    return this->id_;
}

void MapNode::add_vizinho(const long long int id) {
    if (this->eh_vizinho(id)) return;
    this->vizinhos_.push_back(id);
}

void MapNode::add_vizinho(std::vector<long long int>ids) {
    for (const auto &v : ids) {
        if (!this->eh_vizinho(v)) this->vizinhos_.push_back(v);
    }
}

bool MapNode::eh_vizinho(const long long int id) {
    for (const auto &v : this->vizinhos_) {
        if (v == id) return true;
    }
    return false;
}