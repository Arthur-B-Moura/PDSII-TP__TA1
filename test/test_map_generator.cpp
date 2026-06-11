// Testa implementação da classe map_node //
//      >> Teste abertura e fechamento de arquivos
//      >> Teste de métodos básicos
//      >> Testa lógica gerenciamento de arquivos

#include "catch2/catch.hpp"
#include "map_generator.h"
#include <iostream>


TEST_CASE("Basic intialization") {
    MapGenerator m("./maps/map_liberdade.osm");
};

TEST_CASE("Test map generation from OSM file") {
    MapGenerator m("./maps/map_liberdade.osm");
    Map mapa = m.get_mapa();

    SECTION("Nodes corretamente contados") {
        REQUIRE(mapa.node_count() > 0);
        std::cout << "Node count: " << mapa.node_count() << std::endl;
    };

    SECTION("Edges corretamente contados") {
        REQUIRE(mapa.edge_count() > 0);
        std::cout << "Edge count: " << mapa.edge_count() << std::endl;
    };

    // Obs: usando mapa - liberdade
    SECTION("Check distância entre nós") {
        REQUIRE(mapa.has_node(28634767) == true);
        REQUIRE(mapa.has_node(6380526193) == true);
        
        for (const auto& link : mapa.get_neighbors(28634767)) {
            if (link.toNodeId == 6380526193) {
                std::cout << "Distancia = " << link.distance << "km" << std::endl;
                REQUIRE((link.distance > 0.0800 && link.distance < 0.150)); 
                break;
            }
        }
    };

    SECTION("Check leitura de lugares-rua") {
        REQUIRE(mapa.dict_estruturas().size() > 0);
        
        std::cout << mapa.dict_estruturas().at(4600680).nome << std::endl;
        std::cout << mapa.dict_estruturas().at(4600680).tag << std::endl;

        REQUIRE(mapa.dict_estruturas().at(4600680).nodes_id_ref.size() > 0);
        for (long unsigned int i = 0; i < mapa.dict_estruturas().at(4600680).nodes_delta_ref.size(); i++) {
            REQUIRE(mapa.dict_estruturas().at(4600680).nodes_delta_ref[i] == 0);
        }
    };
};