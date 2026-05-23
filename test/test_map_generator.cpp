// Testa implementação da classe map_node //
//      >> Teste abertura e fechamento de arquivos
//      >> Teste de métodos básicos
//      >> Testa lógica gerenciamento de arquivos

#include "catch2/catch.hpp"
#include "map_generator.h"


TEST_CASE("Basic intialization") {
    MapGenerator m("./maps/map.osm");
};