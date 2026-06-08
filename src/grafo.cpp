/**
 * @file    grafo.cpp
 * @brief   Implementação da classe Grafo
 */

#include "grafo.h"
#include <stdexcept>
#include <cmath>
#include <algorithm>
#include <iostream>


/// ----------------------------------- ///
/// Métodos auxiliares para uso interno ///
/// ----------------------------------- ///

double Grafo::haversine_distance(const MapNode& a, const MapNode& b) const {
    double distancia, aux, c_;
    double RAIO = 6371.009; // raio da Terra em km

    // Converte valores para radianos
    double phi1 = a.posicao().latitude_ * M_PI / 180.0;
    double phi2 = b.posicao().latitude_ * M_PI / 180.0;
    double delta_phi = phi2 - phi1;
    double delta_lambda = (b.posicao().longitude_ - 
                           a.posicao().longitude_) * M_PI / 180.0;

    // Formula de distância Haversine
    aux = std::pow(std::sin(delta_phi / 2),2) + std::cos(phi1) * 
          std::cos(phi2) * std::pow(std::sin(delta_lambda / 2),2);
    c_ =  2 * std::atan2(std::sqrt(aux),std::sqrt(1-aux));

    // Distancia entre os pontos, em km
    distancia = RAIO * c_;
    return distancia;
}


bool Grafo::edge_exists(std::vector<Edge> haystack, Edge needle) const {
    if (std::find(haystack.begin(), haystack.end(), needle) != haystack.end()) {
        return true;
    }
    return false;
}

/// ---------------------- ///
/// Construtor e destrutor ///
/// ---------------------- /// 

Grafo::Grafo() {
    this->edge_count_ = 0;
}


Grafo::~Grafo() {
    this->nodes_.clear();
    this->nodes_.rehash(0);

    for (auto& pair : this->adjacency_) {
        pair.second.clear();
    }
    this->adjacency_.clear();
    this->adjacency_.rehash(0);
}


/// --------------------------------------- ///
/// Mutadores - modificam o estado do grafo ///
/// --------------------------------------- ///

void Grafo::add_node(const MapNode& node) {
    if (!this->has_node(node.id())) {
        this->nodes_.insert({node.id(), node});
        this->adjacency_.insert({node.id(), std::vector<Edge>()});
    }
}


void Grafo::add_edge(long long from_id, long long to_id) {
    if((this->has_node(from_id) && this->has_node(to_id)) == false) {
        throw std::invalid_argument("Tentativa de adicionar edge com um ou mais nós não mapeados.");
        return;
    }   
    double distance = this->haversine_distance(this->get_node(from_id),this->get_node(to_id));
    
    // TODO: Add distinção de sentido de ruas
    Edge edge_from_to{to_id,distance};
    Edge edge_to_from{from_id,distance};
    
    std::vector<Edge>& edges_from = this->adjacency_.at(from_id);
    std::vector<Edge>& edges_to = this->adjacency_.at(to_id);
    
    if (!this->edge_exists(edges_from,edge_from_to)) {
        edges_from.push_back(edge_from_to);
        this->edge_count_++;
    }
    if(!this->edge_exists(edges_to,edge_to_from)) {
        edges_to.push_back(edge_to_from);
        this->edge_count_++;
    }
    return;
}


void Grafo::add_edge(long long from_id, std::vector<long long> ids_connected_to) {
    for (const auto& to_id : ids_connected_to) {
        this->add_edge(from_id, to_id);
    }
}


/// --------------------------------------- ///
/// Acessores - leitura do estado do grafo  ///
/// --------------------------------------- ///

const MapNode& Grafo::get_node(long long id) const{
    if (!this->has_node(id)) {
        throw std::invalid_argument("Tentativa de acessar nó não mapeado.");
    }
    return this->nodes_.at(id);
}


const std::vector<Edge>& Grafo::get_neighbors(long long node_id) const {
    if (!this->has_node(node_id)) {
        throw std::invalid_argument("Tentativa de acessar vizinhos de nó não mapeado.");
    }
    return this->adjacency_.at(node_id);
}


bool Grafo::has_node(long long id) const {
    return this->nodes_.count(id) == 1; 
}


int Grafo::node_count() const {
    return this->nodes_.size();
}


int Grafo::edge_count() const {
    return this->edge_count_;
}