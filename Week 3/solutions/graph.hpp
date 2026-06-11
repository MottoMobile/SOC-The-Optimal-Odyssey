#pragma once
#include <vector>
#include <cmath>
#include <fstream>
#include "json.hpp"

struct Node {
    int x, y;
    bool operator==(const Node& o) const { return x == o.x && y == o.y; }
    bool operator!=(const Node& o) const { return !(*this == o); }
    bool operator<(const Node& o)  const { return x < o.x || (x == o.x && y < o.y); }
};

struct NodeHash {
    size_t operator()(const Node& n) const {
        return std::hash<int>()(n.x) ^ (std::hash<int>()(n.y) << 16);
    }
};

class Graph {
public:
    int rows, cols;
    std::vector<std::vector<bool>> obstacle;

    Graph(const nlohmann::json& j) {
        rows = j["grid_size"]["rows"];
        cols = j["grid_size"]["cols"];
        obstacle.assign(rows, std::vector<bool>(cols, false));
        for (auto& ob : j["obstacles"]) {
            int r = ob["y"];
            int c = ob["x"];
            if (r >= 0 && r < rows && c >= 0 && c < cols)
                obstacle[r][c] = true;
        }
    }

    std::vector<Node> get_neighbors(Node cur) const {
        std::vector<Node> nb;
        int dx[] = {0, 0, 1, -1};
        int dy[] = {1, -1, 0, 0};
        for (int i = 0; i < 4; i++) {
            int nx = cur.x + dx[i];
            int ny = cur.y + dy[i];
            if (nx >= 0 && nx < cols && ny >= 0 && ny < rows && !obstacle[ny][nx])
                nb.push_back({nx, ny});
        }
        return nb;
    }
};
