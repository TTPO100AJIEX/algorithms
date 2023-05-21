#include <ios>
#include <iostream>
#include <cstdint>
#include <queue>
#include <vector>
#include <utility>
#include <utility>

class Graph
{
private:
    using Edge = std::pair<unsigned int, unsigned int>;
    std::vector< std::vector<Edge> > edges;

public:
    Graph(unsigned int vertexes) { this->edges.resize(vertexes); }
    void addEdge(unsigned int from, unsigned int to, unsigned int weight) { this->edges[from].emplace_back(to, weight); }

    std::vector<uint64_t> findDistances(unsigned int from)
    {
        constexpr uint64_t INF = UINT64_MAX;
        std::vector<uint64_t> distances(this->edges.size(), INF);
        distances[from] = 0;

        using Result = std::pair<uint64_t, unsigned int>;
        std::priority_queue< Result, std::vector<Result>, std::greater<Result> > to_update;
        to_update.emplace(0, from);

        while (!to_update.empty())
        {
            Result update = to_update.top();
            to_update.pop();
            if (update.first > distances[update.second]) continue;
            for (const Edge& edge : this->edges[update.second])
            {
                uint64_t attempt = distances[update.second] + edge.second;
                if (attempt < distances[edge.first])
                {
                    distances[edge.first] = attempt;
                    to_update.emplace(attempt, edge.first);
                }
            }
        }
        return distances;
    }
};

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    unsigned int n, m;
    std::cin >> n >> m;
    Graph graph(n);
    for (unsigned int i = 0; i < m; ++i)
    {
        unsigned int u, v, w;
        std::cin >> u >> v >> w;
        graph.addEdge(u, v, w);
    }

    for (uint64_t weight : graph.findDistances(0))
    {
        if (weight != 0) std::cout << weight << '\n';
    }
}