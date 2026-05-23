// Testa implementação da classe map_node //
//      >> Teste de métodos básicos

#include "catch2/catch.hpp"
#include "map_node.h"

bool todos_pertencem(std::vector<long long int> ids, MapNode m) {
    for (const auto& i : ids) {
        if (!m.eh_vizinho(i)) return false;
    }
    return true;
}


TEST_CASE("Incialiazção do objeto") {
    Coordenada c = {345,365};
    MapNode o(3,c);

    REQUIRE(o.posicao().latitude_ == c.latitude_);
    REQUIRE(o.posicao().longitude_ == c.longitude_);
};

TEST_CASE("Adiciona serie de vizinhos") {
    std::vector<long long int> v = {4,6,1,3,56,8,235,13,7,4,1};
    MapNode n(4, Coordenada{0,0});

    n.add_vizinho(4);
    CHECK(n.eh_vizinho(4) == true);

    SECTION("Adicionando vetor de vizinhos após add 1") {
        n.add_vizinho(v);
        CHECK(todos_pertencem(v, n) == true);
    }
};

TEST_CASE("Modificação complexa de vizinhos") {
    std::vector<long long int> tmp = {1,2,3,4,3,5,6};
    MapNode map(0, Coordenada{4,25});

    SECTION("Adicionando vetor de vizinhos ao mapa") {
        map.add_vizinho(tmp);
        CHECK(todos_pertencem(tmp,map) == true);
    }

    SECTION("Removendo um vizinho do mapa") {
        map.remove_vizinho(3);
        CHECK(map.eh_vizinho(3) == false);
        CHECK(todos_pertencem(tmp, map) == false);
    }

    SECTION("Re-inserindo vizinho retirado ao mapa") {
        map.add_vizinho(3);
        CHECK(map.eh_vizinho(3) == true);
    }
}