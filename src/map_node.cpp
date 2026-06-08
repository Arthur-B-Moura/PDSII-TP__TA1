/**
 * @file    map_node.cpp
 * @brief   Implementação da classe MapNode e de sua dependência, Coordenada
 */

#include "map_node.h"
#include <stdexcept>

// ============================================================================= //
//                                    Coordenada                                 //
// ============================================================================= //

 
bool Coordenada::isValid() const {
    const bool latValida = (latitude_  >= -90.0  && latitude_  <= 90.0);
    const bool lonValida = (longitude_ >= -180.0 && longitude_ <= 180.0);
    return latValida && lonValida;
}


// ============================================================================= //
//                                    MapNode                                    //
// ============================================================================= //


MapNode::MapNode(const long long int id, Coordenada pos) {
    if (!pos.isValid()) {
        throw (std::invalid_argument("Coordenada inválida"));
    }
    
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