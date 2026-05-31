#include "map_node.h"

// TO-DO: Inserir check coordenada válida
MapNode::MapNode(const long long int id, Coordenada pos) {
    this->id_ = id;
    this->posicao_ = pos;
}

MapNode::~MapNode(){}

Coordenada MapNode::posicao() const {
    return this->posicao_;    
}

long long int MapNode::id() const {
    return this->id_;
}