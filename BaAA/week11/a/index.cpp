#include <ios>
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <utility>

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned int n, k; std::cin >> n >> k;
    std::vector< std::vector< std::pair<unsigned int, unsigned int> > > edges(n);
    for (unsigned int i = 0; i < k; i++)
    {
        unsigned int amount; std::cin >> amount;
        for (unsigned int j = 0; j < amount; j++)
        {
            unsigned int from, to;
            std::cin >> from >> to;
            from--; to--;
            edges[from].emplace_back(to, i + 1);
            edges[to].emplace_back(from, i + 1);
        }
    }


    constexpr unsigned int distanceMax = (1 << 30);
    std::vector<unsigned int> vertexes(n, distanceMax); vertexes[0] = 0;
    std::queue< std::pair<unsigned int, unsigned int> > to_update; to_update.emplace(0, distanceMax);
    while (!to_update.empty())
    {
        std::pair<unsigned int, unsigned int> current = to_update.front();
        to_update.pop();
        for (const std::pair<unsigned int, unsigned int>& edge : edges[current.first])
        {
            unsigned int newDistance = vertexes[current.first] + (current.second == edge.second ? 0 : 1);
            if (vertexes[edge.first] >= newDistance)
            {
                vertexes[edge.first] = newDistance;
                to_update.emplace(edge.first, edge.second);
            }
        }
    }

    std::cout << (vertexes[n - 1] == distanceMax) ? -1 : vertexes[n - 1];
    return 0;
}