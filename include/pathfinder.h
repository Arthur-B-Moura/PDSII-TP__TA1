#ifndef PATHFINDER_H__
#define PATHFINDER_H__

#include <vector>
#include <unordered_map>
#include <string>
#include "grafo.h"

struct PathResult {
    std::vector<long long> node_ids;
    double total_distance;
    bool found;
};

class PathFinder {
private:
    const Grafo& grafo_;

    double heuristic(long long from_id, long long to_id) const;
    double bearing(long long from_id, long long to_id) const;
    std::vector<long long> reconstruct_path(
        const std::unordered_map<long long, long long>& came_from,
        long long end_id
    ) const;

public:
    PathFinder(const Grafo& grafo);
    ~PathFinder();

    PathResult find_path(long long start_id, long long end_id) const;
    std::vector<std::string> build_instructions(const PathResult& result) const;
};

#endif
