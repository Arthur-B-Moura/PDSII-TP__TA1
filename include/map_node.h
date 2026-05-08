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
    std::vector<long long> vizinhos_;

public:
    MapNode(const long long int id);
    ~MapNode();
    const long long int id();
    void add_vizinho();
};

#endif