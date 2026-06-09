#include "pathfinder.h"
#include <cmath>
#include <queue>
#include <limits>
#include <algorithm>

// Raio da Terra em metros, usado nas contas de distância geográfica
static const double R = 6371000.0;

// Converte graus para radianos (necessário para as funções trigonométricas do cmath)
static double deg2rad(double deg) {
    return deg * M_PI / 180.0;
}

PathFinder::PathFinder(const Grafo& grafo) : grafo_(grafo) {}

PathFinder::~PathFinder() {}

// Estima a distância em linha reta entre dois nós usando a fórmula de Haversine
// Serve como "chute" do A* — o custo mínimo possível entre dois pontos no mapa
double PathFinder::heuristic(long long from_id, long long to_id) const {
    const MapNode& a = grafo_.get_node(from_id);
    const MapNode& b = grafo_.get_node(to_id);

    double lat1 = deg2rad(a.posicao().latitude_);
    double lat2 = deg2rad(b.posicao().latitude_);
    double dlat = lat2 - lat1;
    double dlon = deg2rad(b.posicao().longitude_ - a.posicao().longitude_);

    double x = sin(dlat / 2) * sin(dlat / 2) +
               cos(lat1) * cos(lat2) *
               sin(dlon / 2) * sin(dlon / 2);

    return 2.0 * R * atan2(sqrt(x), sqrt(1.0 - x));
}

// Calcula o ângulo de direção (em graus) entre dois nós
// 0° = Norte, 90° = Leste, 180° = Sul, 270° = Oeste
double PathFinder::bearing(long long from_id, long long to_id) const {
    const MapNode& a = grafo_.get_node(from_id);
    const MapNode& b = grafo_.get_node(to_id);

    double lat1 = deg2rad(a.posicao().latitude_);
    double lat2 = deg2rad(b.posicao().latitude_);
    double dlon = deg2rad(b.posicao().longitude_ - a.posicao().longitude_);

    double y = sin(dlon) * cos(lat2);
    double x = cos(lat1) * sin(lat2) - sin(lat1) * cos(lat2) * cos(dlon);

    double angle = atan2(y, x) * 180.0 / M_PI;
    return fmod(angle + 360.0, 360.0);
}

// Reconstrói o caminho do fim até o início usando o mapa came_from
// came_from guarda, para cada nó, qual foi o nó anterior no caminho ótimo
std::vector<long long> PathFinder::reconstruct_path(
    const std::unordered_map<long long, long long>& came_from,
    long long end_id
) const {
    std::vector<long long> path;
    long long current = end_id;

    while (came_from.count(current)) {
        path.push_back(current);
        current = came_from.at(current);
    }
    path.push_back(current); // adiciona o nó inicial
    std::reverse(path.begin(), path.end()); // inverte para ficar início -> fim
    return path;
}

// Algoritmo A*: encontra o caminho mais curto entre start_id e end_id
// Usa uma fila de prioridade para sempre explorar o nó mais promissor primeiro
// f(n) = g(n) + h(n), onde g = custo real acumulado, h = estimativa até o destino
PathResult PathFinder::find_path(long long start_id, long long end_id) const {
    using pair_t = std::pair<double, long long>;

    // Fila de prioridade ordenada pelo menor f(n) — o nó mais promissor sai primeiro
    std::priority_queue<pair_t, std::vector<pair_t>, std::greater<pair_t>> open_set;

    // g_score[n] = menor custo real conhecido do início até n
    std::unordered_map<long long, double> g_score;

    // came_from[n] = nó anterior no caminho ótimo até n
    std::unordered_map<long long, long long> came_from;

    g_score[start_id] = 0.0;
    open_set.push({heuristic(start_id, end_id), start_id});

    while (!open_set.empty()) {
        long long current = open_set.top().second;
        open_set.pop();

        // Chegou ao destino — reconstrói e retorna o caminho
        if (current == end_id) {
            PathResult result;
            result.node_ids = reconstruct_path(came_from, end_id);
            result.total_distance = g_score[end_id];
            result.found = true;
            return result;
        }

        // Explora os vizinhos do nó atual
        for (const Edge& edge : grafo_.get_neighbors(current)) {
            double tentative = g_score[current] + edge.distance;

            // Se encontrou um caminho mais curto até esse vizinho, atualiza
            if (!g_score.count(edge.toNodeId) || tentative < g_score[edge.toNodeId]) {
                g_score[edge.toNodeId] = tentative;
                came_from[edge.toNodeId] = current;
                double f = tentative + heuristic(edge.toNodeId, end_id);
                open_set.push({f, edge.toNodeId});
            }
        }
    }

    // Fila esgotou sem encontrar o destino
    return {{}, 0.0, false};
}

// Converte o caminho em instruções de texto usando o ângulo entre nós consecutivos
std::vector<std::string> PathFinder::build_instructions(const PathResult& result) const {
    std::vector<std::string> instructions;

    if (!result.found || result.node_ids.size() < 2)
        return instructions;

    for (size_t i = 0; i + 1 < result.node_ids.size(); i++) {
        long long from = result.node_ids[i];
        long long to   = result.node_ids[i + 1];

        double dist  = heuristic(from, to);
        double angle = bearing(from, to);

        std::string direcao;
        if      (angle < 22.5  || angle >= 337.5) direcao = "norte";
        else if (angle < 67.5)                    direcao = "nordeste";
        else if (angle < 112.5)                   direcao = "leste";
        else if (angle < 157.5)                   direcao = "sudeste";
        else if (angle < 202.5)                   direcao = "sul";
        else if (angle < 247.5)                   direcao = "sudoeste";
        else if (angle < 292.5)                   direcao = "oeste";
        else                                      direcao = "noroeste";

        instructions.push_back(
            "Siga em direcao ao " + direcao + " por " + std::to_string((int)dist) + "m"
        );
    }

    return instructions;
}
