// Testa implementação da classe map_node //
//      >> Teste abertura e fechamento de arquivos
//      >> Teste de métodos básicos
//      >> Testa lógica gerenciamento de arquivos

#include "catch2/catch.hpp"
#include "map_generator.h"
#include <iostream>


TEST_CASE("Basic intialization") {
    MapGenerator m("./maps/map.osm");
};

TEST_CASE("Test map generation from OSM file") {
    MapGenerator m("./maps/map.osm");
    Map mapa = m.get_mapa();
    REQUIRE(mapa.node_count() > 0);
    std::cout << "Node count: " << mapa.node_count() << std::endl;
    // REQUIRE(mapa.edge_count() > 0);
};