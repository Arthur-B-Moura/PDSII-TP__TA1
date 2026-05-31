// Testa implementação da classe grafo //
//      >> Teste de métodos básicos

#include "catch2/catch.hpp"
#include "grafo.h"

TEST_CASE("Incialiazção do objeto") {
    Grafo g;

    REQUIRE(g.node_count() == 0);
    REQUIRE(g.edge_count() == 0);
};

TEST_CASE("Verifica has_node") {
    Grafo g;
    MapNode n1(1 ,{0.0,0.0});

    REQUIRE(g.has_node(1) == false);

    g.add_node(n1);
    REQUIRE(g.has_node(1) == true);
    REQUIRE(g.has_node(0) == false);
};

TEST_CASE("Inserção de nós e edges") {
    Grafo g;

    MapNode n1(1, {0.0, 0.0});
    MapNode n2(2, {0.0, 1.0});
    MapNode n3(3, {1.0, 0.0});

    g.add_node(n1);
    g.add_node(n2);
    g.add_node(n3);

    REQUIRE(g.node_count() == 3);

    g.add_edge(1, 2);
    g.add_edge(2, 3);

    REQUIRE(g.edge_count() == 4);
};

TEST_CASE("Verifica designação de vizinhos") {
    Grafo g;

    MapNode n1(1, {0.0, 0.0});
    MapNode n2(2, {0.0, 1.0});
    MapNode n3(3, {1.0, 0.0});
 
    g.add_node(n1);
    g.add_node(n2);
    g.add_node(n3);

    SECTION ("Nenhuma edge ou vizinho prsente") {
        REQUIRE(g.get_neighbors(1).size() == 0);
        REQUIRE(g.get_neighbors(2).size() == 0);
        REQUIRE(g.get_neighbors(3).size() == 0);
    }

    SECTION ("Edges presentes") {
        g.add_edge(1, 2);
        g.add_edge(2, 3);

        REQUIRE(g.get_neighbors(1).size() == 1);
        REQUIRE(g.get_neighbors(2).size() == 2);
        REQUIRE(g.get_neighbors(3).size() == 1);

        REQUIRE(g.get_neighbors(1)[0].toNodeId == 2);
        REQUIRE((g.get_neighbors(2)[0].toNodeId == 1 || g.get_neighbors(2)[0].toNodeId == 3));
        REQUIRE(g.get_neighbors(3)[0].toNodeId == 2);
    }
};


TEST_CASE("Catch exceptions") {
    Grafo g;
    MapNode n1(1, {0.0, 0.0});

    SECTION ("Acessar nó ou vizinhos de nó não mapeado") {
        REQUIRE_THROWS(g.get_node(1));
        REQUIRE_THROWS_AS(g.get_neighbors(1), std::invalid_argument);
        REQUIRE_THROWS_AS(g.add_edge(1, 2), std::invalid_argument);
    }

    SECTION("Adição de edge com um ou mais nós não mapeados") {
        g.add_node(n1);
        REQUIRE_THROWS_AS(g.add_edge(1, 2), std::invalid_argument);
        REQUIRE_THROWS_AS(g.add_edge(2, 1), std::invalid_argument);
    }
};


TEST_CASE("Verifica cálculo de distância") {
    Grafo g;

    MapNode n1(1, {0.0, 0.0});
    MapNode n2(2, {0.0, 1.0});
    MapNode n3(3, {1.0, 0.0});

    g.add_node(n1);
    g.add_node(n2);
    g.add_node(n3);

    g.add_edge(1, 2);
    g.add_edge(2, 3);

    REQUIRE(g.get_neighbors(1)[0].distance == Approx(111319.49079).epsilon(0.00001));
    REQUIRE(g.get_neighbors(2)[0].distance == Approx(111319.49079).epsilon(0.00001));
    REQUIRE(g.get_neighbors(2)[1].distance == Approx(157249.38127).epsilon(0.00001));
    REQUIRE(g.get_neighbors(3)[0].distance == Approx(157249.38127).epsilon(0.00001));
};


TEST_CASE("Verifica edge duplicada") {
    Grafo g;

    MapNode n1(1, {0.0, 0.0});
    MapNode n2(2, {0.0, 1.0});

    g.add_node(n1);
    g.add_node(n2);

    g.add_edge(1, 2);
    g.add_edge(1, 2);
    g.add_edge(2, 1);

    REQUIRE(g.edge_count() == 4);
};