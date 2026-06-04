#ifndef MAP_NODE_H__
#define MAP_NODE_H__

#include <string>
#include <vector>

struct Coordenada {
    double latitude_;
    double longitude_;
};

class MapNode {
private:
    long long int id_;
    Coordenada posicao_;
    
public:
    // TO-DO: Adicionar construtor que inclua vizinhos

    // Pré-condição: assume id válido
    MapNode(const long long int id);

    // Pré-condição: assume id válido
    MapNode(const long long int id, Coordenada pos);
    
    ~MapNode();

    Coordenada posicao() const;
    
    long long int id() const;
};

#endif