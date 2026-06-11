#pragma once
#include <unordered_map>
#include <queue>
#include <vector>
#include <cmath>
#include <limits>
#include "graph.hpp"

enum class Heuristic { ZERO, EUCLIDEAN, MANHATTAN };

inline double heuristic(const Node& a, const Node& b, Heuristic type) {
    switch (type) {
        case Heuristic::ZERO:      return 0.0;
        case Heuristic::EUCLIDEAN: return std::sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y));
        case Heuristic::MANHATTAN: return std::abs(a.x-b.x) + std::abs(a.y-b.y);
    }
    return 0.0;
}

struct SearchResult {
    bool path_found;
    int  path_length;
    int  nodes_explored;
    double time_ms;
};

SearchResult run_astar(const Graph& g, Node start, Node goal, Heuristic h_type) {
    using PQ = std::priority_queue<
        std::pair<double, Node>,
        std::vector<std::pair<double, Node>>,
        std::greater<std::pair<double, Node>>
    >;

    auto encode = [&](const Node& n) { return n.y * g.cols + n.x; };

    int sz = g.rows * g.cols;
    std::vector<double> g_cost(sz, std::numeric_limits<double>::infinity());
    std::vector<bool>   visited(sz, false);

    PQ open;
    g_cost[encode(start)] = 0.0;
    open.push({heuristic(start, goal, h_type), start});

    int nodes_explored = 0;
    bool found = false;

    auto t0 = std::chrono::high_resolution_clock::now();

    while (!open.empty()) {
        auto [f, cur] = open.top(); open.pop();

        int id = encode(cur);
        if (visited[id]) continue;
        visited[id] = true;
        nodes_explored++;

        if (cur == goal) { found = true; break; }

        for (const Node& nb : g.get_neighbors(cur)) {
            int nb_id = encode(nb);
            double new_g = g_cost[id] + 1.0;
            if (new_g < g_cost[nb_id]) {
                g_cost[nb_id] = new_g;
                double f_val = new_g + heuristic(nb, goal, h_type);
                open.push({f_val, nb});
            }
        }
    }

    auto t1 = std::chrono::high_resolution_clock::now();
    double ms = std::chrono::duration<double, std::milli>(t1 - t0).count();

    int path_len = found ? (int)g_cost[encode(goal)] : -1;
    return {found, path_len, nodes_explored, ms};
}
