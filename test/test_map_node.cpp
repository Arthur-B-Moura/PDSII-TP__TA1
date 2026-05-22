// Testa implementação da classe map_node //
//      >> Teste de métodos básicos

#include "catch2/catch.hpp"
#include "map_node.h"

TEST_CASE("Inicialização simples do objeto") {
    MapNode m(5);

    REQUIRE(m.id() == 5);
    REQUIRE(m.posicao() == std::nullopt);
    REQUIRE(m.eh_vizinho(5) == false);
};