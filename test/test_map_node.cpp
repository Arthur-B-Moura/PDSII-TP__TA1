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

TEST_CASE("Inicialização simples do objeto") {
    MapNode m(5);

    REQUIRE(m.id() == 5);
    REQUIRE(m.posicao() == std::nullopt);
    REQUIRE(m.eh_vizinho(5) == false);
};

TEST_CASE("Adiciona serie de vizinhos") {
    std::vector<long long int> v = {4,6,1,3,56,8,235,13,7,4,1};
    MapNode n(4);

    n.add_vizinho(4);
    CHECK(n.eh_vizinho(4) == true);

    SECTION("Adicionando vetor de vizinhos após add 1") {
        n.add_vizinho(v);
        CHECK(todos_pertencem(v, n) == true);
    }
};