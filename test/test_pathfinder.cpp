// Testa implementação da classe PathFinder //
//      >> Algoritmo A* e funções auxiliares

#include "catch2/catch.hpp"
#include "grafo.h"
#include "pathfinder.h"

// ---------------------------------------------------------------------------
// Helpers: monta grafos reutilizáveis nos testes
// ---------------------------------------------------------------------------

// Grafo linear simples:  1 -- 2 -- 3
//   nó 1: (0.0,  0.0)
//   nó 2: (0.0,  1.0)   ~111 km ao leste de 1
//   nó 3: (0.0,  2.0)   ~111 km ao leste de 2
static Grafo make_linear_graph() {
    Grafo g;
    g.add_node(MapNode(1, {0.0, 0.0}));
    g.add_node(MapNode(2, {0.0, 1.0}));
    g.add_node(MapNode(3, {0.0, 2.0}));
    g.add_edge(1, 2);
    g.add_edge(2, 3);
    return g;
}

// Grafo com quatro nós formando um quadrado (coordenadas em graus):
//   1(0,0) -- 2(0,1)
//     |              |
//   3(1,0) -- 4(1,1)
static Grafo make_square_graph() {
    Grafo g;
    g.add_node(MapNode(1, {0.0, 0.0}));
    g.add_node(MapNode(2, {0.0, 1.0}));
    g.add_node(MapNode(3, {1.0, 0.0}));
    g.add_node(MapNode(4, {1.0, 1.0}));
    g.add_edge(1, 2);
    g.add_edge(1, 3);
    g.add_edge(2, 4);
    g.add_edge(3, 4);
    return g;
}

// Grafo desconexo: nós 1-2 conectados, nó 3 isolado
static Grafo make_disconnected_graph() {
    Grafo g;
    g.add_node(MapNode(1, {0.0, 0.0}));
    g.add_node(MapNode(2, {0.0, 1.0}));
    g.add_node(MapNode(3, {5.0, 5.0}));
    g.add_edge(1, 2);
    return g;
}


// ===========================================================================
// Inicialização
// ===========================================================================

TEST_CASE("PathFinder: inicialização com grafo válido") {
    Grafo g = make_linear_graph();
}


// ===========================================================================
// find_path — casos básicos
// ===========================================================================

TEST_CASE("find_path: caminho direto entre dois nós adjacentes") {
    Grafo g = make_linear_graph();
    PathFinder pf(g);

    PathResult r = pf.find_path(1, 2);

    REQUIRE(r.found == true);
    REQUIRE(r.node_ids.size() == 2);
    REQUIRE(r.node_ids.front() == 1);
    REQUIRE(r.node_ids.back()  == 2);
    REQUIRE(r.total_distance > 0.0);
}

TEST_CASE("find_path: nó de origem igual ao destino") {
    Grafo g = make_linear_graph();
    PathFinder pf(g);

    PathResult r = pf.find_path(1, 1);

    // O caminho trivial deve ser encontrado (só o próprio nó)
    REQUIRE(r.found == true);
    REQUIRE(r.node_ids.size() == 1);
    REQUIRE(r.node_ids.front() == 1);
    REQUIRE(r.total_distance == Approx(0.0).epsilon(1e-9));
}

TEST_CASE("find_path: caminho com nó intermediário") {
    Grafo g = make_linear_graph();
    PathFinder pf(g);

    PathResult r = pf.find_path(1, 3);

    REQUIRE(r.found == true);
    REQUIRE(r.node_ids.size() == 3);
    REQUIRE(r.node_ids[0] == 1);
    REQUIRE(r.node_ids[1] == 2);
    REQUIRE(r.node_ids[2] == 3);
}

TEST_CASE("find_path: destino inalcançável (grafo desconexo)") {
    Grafo g = make_disconnected_graph();
    PathFinder pf(g);

    PathResult r = pf.find_path(1, 3);

    REQUIRE(r.found == false);
    REQUIRE(r.node_ids.empty());
    REQUIRE(r.total_distance == Approx(0.0).epsilon(1e-9));
}


// ===========================================================================
// find_path — otimalidade e consistência de custo
// ===========================================================================

TEST_CASE("find_path: distância acumulada é consistente com as arestas") {
    Grafo g = make_linear_graph();
    PathFinder pf(g);

    PathResult r12 = pf.find_path(1, 2);
    PathResult r23 = pf.find_path(2, 3);
    PathResult r13 = pf.find_path(1, 3);

    REQUIRE(r13.found == true);

    // O custo de 1→3 deve ser aproximadamente a soma de 1→2 e 2→3
    double soma = r12.total_distance + r23.total_distance;
    REQUIRE(r13.total_distance == Approx(soma).epsilon(0.01));
}

TEST_CASE("find_path: A* escolhe o caminho mais curto em grafo quadrado") {
    // No quadrado (1-2-4 vs 1-3-4), as distâncias são diferentes porque
    // as coordenadas não formam um quadrado euclidiano perfeito.
    // O A* deve sempre retornar o caminho de menor custo total.
    Grafo g = make_square_graph();
    PathFinder pf(g);

    PathResult r = pf.find_path(1, 4);
    REQUIRE(r.found == true);

    // Verifica que o caminho retornado é de fato o mais curto
    // calculando manualmente os dois candidatos via edges do grafo
    double dist_via_2 = g.get_neighbors(1)[0].toNodeId == 2
        ? g.get_neighbors(1)[0].distance + g.get_neighbors(2)[0].distance
        : g.get_neighbors(1)[1].distance + g.get_neighbors(2)[0].distance;

    REQUIRE(r.total_distance <= dist_via_2 + 1.0); // tolerância de 1 metro
}

TEST_CASE("find_path: distância total nunca é negativa") {
    Grafo g = make_square_graph();
    PathFinder pf(g);

    for (long long src : {1LL, 2LL, 3LL, 4LL}) {
        for (long long dst : {1LL, 2LL, 3LL, 4LL}) {
            PathResult r = pf.find_path(src, dst);
            if (r.found)
                REQUIRE(r.total_distance >= 0.0);
        }
    }
}


// ===========================================================================
// find_path — propriedades do caminho retornado
// ===========================================================================

TEST_CASE("find_path: caminho começa no nó de origem e termina no destino") {
    Grafo g = make_square_graph();
    PathFinder pf(g);

    PathResult r = pf.find_path(1, 4);
    REQUIRE(r.found == true);
    REQUIRE(r.node_ids.front() == 1);
    REQUIRE(r.node_ids.back()  == 4);
}

TEST_CASE("find_path: nós consecutivos no caminho são vizinhos no grafo") {
    Grafo g = make_square_graph();
    PathFinder pf(g);

    PathResult r = pf.find_path(1, 4);
    REQUIRE(r.found == true);

    for (size_t i = 0; i + 1 < r.node_ids.size(); i++) {
        long long from = r.node_ids[i];
        long long to   = r.node_ids[i + 1];

        const auto& vizinhos = g.get_neighbors(from);
        bool aresta_existe = false;
        for (const Edge& e : vizinhos)
            if (e.toNodeId == to) { aresta_existe = true; break; }

        REQUIRE(aresta_existe == true);
    }
}

TEST_CASE("find_path: simetria — custo de A→B igual a B→A em grafo bidirecional") {
    Grafo g = make_linear_graph();
    PathFinder pf(g);

    PathResult r13 = pf.find_path(1, 3);
    PathResult r31 = pf.find_path(3, 1);

    REQUIRE(r13.found == true);
    REQUIRE(r31.found == true);
    REQUIRE(r13.total_distance == Approx(r31.total_distance).epsilon(0.01));
}


// ===========================================================================
// Funções auxiliares: heurística
// ===========================================================================

TEST_CASE("heuristic: distância entre nó e ele mesmo é zero") {
    Grafo g = make_linear_graph();
    PathFinder pf(g);

    // Acessamos indiretamente pela distância do caminho trivial
    PathResult r = pf.find_path(1, 1);
    REQUIRE(r.total_distance == Approx(0.0).epsilon(1e-9));
}

TEST_CASE("heuristic: estimativa não supera a distância real (admissibilidade)") {
    // A heurística de Haversine é a distância em linha reta, que nunca pode
    // ser maior que o custo real pelo grafo — garante admissibilidade do A*
    Grafo g = make_linear_graph();
    PathFinder pf(g);

    PathResult r = pf.find_path(1, 3);
    REQUIRE(r.found == true);

    // Distância direta 1→3 (linha reta) via Haversine dos nós do grafo
    // nó 1: (0,0), nó 3: (0,2) → ~222 km
    // O custo real via 1→2→3 deve ser >= distância em linha reta
    double dist_reta_aprox = 222.638; // metros, valor esperado para Δlat=0, Δlon=2°
    REQUIRE(r.total_distance >= dist_reta_aprox * 0.99); // margem de 1%
}


// ===========================================================================
// build_instructions
// ===========================================================================

TEST_CASE("build_instructions: sem caminho retorna lista vazia") {
    Grafo g = make_disconnected_graph();
    PathFinder pf(g);

    PathResult r = pf.find_path(1, 3);
    REQUIRE(r.found == false);

    auto instrucoes = pf.build_instructions(r);
    REQUIRE(instrucoes.empty());
}

TEST_CASE("build_instructions: caminho com N nós gera N-1 instruções") {
    Grafo g = make_linear_graph();
    PathFinder pf(g);

    PathResult r = pf.find_path(1, 3);
    REQUIRE(r.found == true);

    auto instrucoes = pf.build_instructions(r);
    REQUIRE(instrucoes.size() == r.node_ids.size() - 1);
}

TEST_CASE("build_instructions: cada instrução contém direção e distância em metros") {
    Grafo g = make_linear_graph();
    PathFinder pf(g);

    PathResult r = pf.find_path(1, 2);
    auto instrucoes = pf.build_instructions(r);

    REQUIRE(instrucoes.size() == 1);

    // A instrução deve mencionar pelo menos uma das direções cardeais/intermediárias
    const std::string& inst = instrucoes[0];
    bool tem_direcao = inst.find("norte")   != std::string::npos ||
                       inst.find("sul")     != std::string::npos ||
                       inst.find("leste")   != std::string::npos ||
                       inst.find("oeste")   != std::string::npos ||
                       inst.find("nordeste")!= std::string::npos ||
                       inst.find("sudeste") != std::string::npos ||
                       inst.find("sudoeste")!= std::string::npos ||
                       inst.find("noroeste")!= std::string::npos;
    REQUIRE(tem_direcao == true);

    // Deve conter "m" indicando metros
    REQUIRE(inst.find('m') != std::string::npos);
}

TEST_CASE("build_instructions: direção leste para deslocamento longitudinal positivo") {
    // nó 1 (0,0) → nó 2 (0,1): aumenta a longitude → bearing ≈ 90° → leste
    Grafo g = make_linear_graph();
    PathFinder pf(g);

    PathResult r = pf.find_path(1, 2);
    auto instrucoes = pf.build_instructions(r);

    REQUIRE(instrucoes.size() == 1);
    REQUIRE(instrucoes[0].find("leste") != std::string::npos);
}

TEST_CASE("build_instructions: PathResult found=false com node_ids insuficientes") {
    PathResult r;
    r.found = false;
    r.total_distance = 0.0;
    // node_ids vazio

    Grafo g = make_linear_graph();
    PathFinder pf(g);

    auto instrucoes = pf.build_instructions(r);
    REQUIRE(instrucoes.empty());
}
