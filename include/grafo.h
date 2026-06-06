#ifndef GRAFO_H__
#define GRAFO_H__

#include <vector>
#include <unordered_map>
#include "map_node.h"

struct Edge {
    long long toNodeId;
    double distance;

    bool operator==(Edge b) {
        return ((this->toNodeId == b.toNodeId) && (this->distance == b.distance));
    }
};

class Grafo {
protected:
    std::unordered_map<long long, MapNode> nodes_;
    /// @brief Adjacency list: mapeia id de nó para vetor de edges (vizinhos)   
    std::unordered_map<long long, std::vector<Edge>> adjacency_;
    int edge_count_;

    double haversine_distance(const MapNode& a, const MapNode& b) const;
    bool edge_exists(std::vector<Edge> haystack, Edge needle) const;

public:
    Grafo();
    ~Grafo();

    void add_node(const MapNode& node);
    void add_edge(long long from_id, long long to_id);
    void add_edge(long long from_id, std::vector<long long> ids_connected_to);

    const MapNode& get_node(long long id) const;
    const std::vector<Edge>& get_neighbors(long long node_id) const;

    bool has_node(long long id) const;
    int node_count() const;
    int edge_count() const;
};

#endif
