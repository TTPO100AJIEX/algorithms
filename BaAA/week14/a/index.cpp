#include <ios>
#include <iostream>
#include <cstdint>
#include <set>
#include <vector>
#include <utility>

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    unsigned int n, m;
    std::cin >> n >> m;

    using Edge = std::pair<unsigned int, unsigned int>;
    std::vector< std::vector<Edge> > edges(n);
    for (unsigned int i = 0; i < m; ++i)
    {
        unsigned int from, to, weight;
        std::cin >> from >> to >> weight;
        edges[from].emplace_back(to, weight);
    }

    constexpr uint64_t INF = UINT64_MAX;
    std::vector<uint64_t> distances(n, INF);
    distances[0] = 0;

    auto cmp = [&](unsigned int a, unsigned int b)
    {
        if (distances[a] == distances[b]) return a < b;
        return distances[a] < distances[b];
    };
    std::set<unsigned int, decltype(cmp)> to_update(cmp);
    to_update.insert(0);
    while (!to_update.empty())
    {
        const unsigned int from = *(to_update.begin());
        to_update.erase(to_update.begin());
        for (const Edge& edge : edges[from])
        {
            uint64_t attempt_distance = distances[from] + edge.second;
            if (attempt_distance < distances[edge.first])
            {
                to_update.erase(edge.first);
                distances[edge.first] = attempt_distance;
                to_update.emplace(edge.first);
            }
        }
    }

    for (unsigned int i = 1; i < n; ++i) std::cout << distances[i] << '\n';
}