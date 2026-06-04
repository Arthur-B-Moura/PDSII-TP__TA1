// Testa implementação da classe map_node //
//      >> Teste de métodos básicos

#include "catch2/catch.hpp"
#include "map_node.h"


TEST_CASE("Incialiazção do objeto") {
    Coordenada c = {345,365};
    MapNode o(3,c);

    REQUIRE(o.posicao().latitude_ == c.latitude_);
    REQUIRE(o.posicao().longitude_ == c.longitude_);
};
