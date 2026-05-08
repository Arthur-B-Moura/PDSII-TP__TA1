#ifndef GRAFO_H__
#define GRAFO_H__

#include <vector>
#include <unordered_map>
#include "map_node.h"

struct Edge {
    long long toNodeId;
    double distance;
};

class Grafo {
protected:
    std::unordered_map<long long, MapNode> nodes_;
    std::unordered_map<long long, std::vector<Edge>> adjacency_;
    int edge_count_;

    double haversine_distance(const MapNode& a, const MapNode& b) const;

public:
    Grafo();
    ~Grafo();

    void add_node(const MapNode& node);
    void add_edge(long long from_id, long long to_id);

    const MapNode& get_node(long long id) const;
    const std::vector<Edge>& get_neighbors(long long node_id) const;

    bool has_node(long long id) const;
    int node_count() const;
    int edge_count() const;
};

#endif
