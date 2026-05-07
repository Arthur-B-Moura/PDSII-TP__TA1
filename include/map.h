#ifndef MAP_H__
#define MAP_H__

#include "grafo.h"
#include <string>
#include <vector>
#include <unordered_map>

// Unidade-espaço lugar/contrução 
struct LugarMap {
    std::string tag;
    std::vector<long long> nodes_id_ref;    // Nós (cruzamento) para poligono-objeto
    std::vector<long long> nodes_delta_ref; // Distância dos nós para posicionamento das arestas do poligono-objeto
};


class Map : Grafo{
private:
    std::string nome_;
    std::string descricao_;
    std::unordered_map<long long, LugarMap> dict_estruturas_;

public:
    Map();
    
    Map(Grafo grafo);
    
    Map(Grafo grafo, std::unordered_map<long long, LugarMap> lugares);

    ~Map();

    void insere_lugar();

    void remove_lugar();

    std::string nome();
    
    std::string descricao();
};


#endif