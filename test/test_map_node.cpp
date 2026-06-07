/**
 * @file    test_map_node.cpp
 * @brief   Testa implementação da classe map_node //
 *      >> Teste de métodos básicos
 *      >> Testa lógica de validação de coordenada
 *      >> Testa lançamento de exceção para coordenada inválida
 */

#include "catch2/catch.hpp"
#include "map_node.h"
#include <stdexcept>


TEST_CASE("Incialiazção do objeto") {
    Coordenada c = {-19.8629611, -43.9551055};
    MapNode o(3,c);

    REQUIRE(o.posicao().latitude_ == c.latitude_);
    REQUIRE(o.posicao().longitude_ == c.longitude_);
};

TEST_CASE("Teste de coordenada inválida") {
    Coordenada c = {345,365};
    REQUIRE(c.isValid() == false);
    REQUIRE_THROWS(MapNode(3, c));
};