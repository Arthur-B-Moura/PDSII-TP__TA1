#ifndef MAP_NODE_H__
#define MAP_NODE_H__

#include <string>
#include <vector>
#include <optional>

struct Coordenada {
    double latitude_;
    double longitude_;
};

class MapNode {
private:
    long long int id_;
    std::optional<Coordenada> posicao_;
    std::vector<long long int> vizinhos_;

public:
    // TO-DO: Adicionar construtor que inclua vizinhos

    // Pré-condição: assume id válido
    MapNode(const long long int id);

    // Pré-condição: assume id válido
    MapNode(const long long int id, Coordenada pos);
    
    ~MapNode();

    std::optional<Coordenada> posicao();
    
    long long int id();
    
    void add_vizinho(const long long int id);

    void add_vizinho(std::vector<long long int>ids);
    
    bool eh_vizinho(const long long int id);
};

#endif