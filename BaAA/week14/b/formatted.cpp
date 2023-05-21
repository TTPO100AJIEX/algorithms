#include <ios>
#include <iostream>
#include <cstdint>
#include <vector>
#include <tuple>
#include <algorithm>

class Graph {
private:
    using Edge = std::tuple<unsigned int, unsigned int, int>;
    std::vector<Edge> edges_;
    unsigned int vertexes_;

public:
    Graph(unsigned int vertexes, unsigned int edges) : vertexes_(vertexes) {
        this->edges_.reserve(edges);
    }
    void addEdge(unsigned int from, unsigned int to, int weight) {
        this->edges_.emplace_back(from, to, weight);
    }

    std::vector<int64_t> findDistances(unsigned int from) {
        constexpr int64_t kInf = INT64_MAX;
        std::vector<int64_t> distances(this->vertexes_, kInf);
        distances[from] = 0;

        for (unsigned int i = 0; i < this->vertexes_ - 1; ++i) {
            bool updated = false;
            for (const Edge& edge : this->edges_) {
                if (distances[std::get<0>(edge)] == kInf) {
                    continue;
                }
                if (distances[std::get<1>(edge)] >
                    distances[std::get<0>(edge)] + std::get<2>(edge)) {
                    distances[std::get<1>(edge)] = distances[std::get<0>(edge)] + std::get<2>(edge);
                    updated = true;
                }
            }
            if (!updated) {
                break;
            }
        }

        std::vector<unsigned int> negative_loops;
        for (const Edge& edge : this->edges_) {
            if (distances[std::get<1>(edge)] > distances[std::get<0>(edge)] + std::get<2>(edge)) {
                negative_loops.push_back(std::get<1>(edge));
            }
        }
        for (unsigned int vertex : negative_loops) {
            distances[vertex] = INT64_MIN / 2;
        }

        return distances;
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned int n, m;
    std::cin >> n >> m;
    Graph graph(n, m);
    for (unsigned int i = 0; i < m; ++i) {
        unsigned int u, v;
        int w;
        std::cin >> u >> v >> w;
        graph.addEdge(u, v, w);
    }

    for (int64_t weight : graph.findDistances(0)) {
        if (weight == 0) {
            continue;
        }
        if (weight == INT64_MIN / 2) {
            std::cout << "-inf\n";
        } else {
            std::cout << weight << '\n';
        }
    }
}