#include <ios>
#include <iostream>
#include <vector>
#include <queue>


int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, x1, y1, x2, y2;
    std::cin >> n >> x1 >> y1 >> x2 >> y2;

    using Vertex = std::pair<int, int>;
    constexpr unsigned int distanceMax = (1 << 30);

    std::vector< std::vector<unsigned int> > distance(n, std::vector<unsigned int>(n, distanceMax));
    std::vector< std::vector<Vertex> > previous(n, std::vector<Vertex>(n));
    --x1; --y1; --x2; --y2; distance[x1][y1] = 0; previous[x1][y1] = { -1, -1 };

    std::queue<Vertex> to_update;
    to_update.emplace(x1, y1);
    while (distance[x2][y2] == distanceMax)
    {
        Vertex current = to_update.front();
        to_update.pop();

        Vertex siblings[8] = {
            { current.first + 2, current.second + 1 },
            { current.first + 2, current.second - 1 },
            { current.first - 2, current.second + 1 },
            { current.first - 2, current.second - 1 },
            { current.first + 1, current.second + 2 },
            { current.first + 1, current.second - 2 },
            { current.first - 1, current.second + 2 },
            { current.first - 1, current.second - 2 }
        };
        for (const Vertex& sibling : siblings)
        {
            if (sibling.first < 0 || sibling.second < 0 || sibling.first >= n || sibling.second >= n || distance[sibling.first][sibling.second] != distanceMax) continue;
            to_update.push(sibling);
            distance[sibling.first][sibling.second] = distance[current.first][current.second] + 1;
            previous[sibling.first][sibling.second] = current;
        }
    }

    std::cout << distance[x2][y2] << '\n';
    Vertex current = { x2, y2 };
    std::vector<Vertex> path;
    while (current.first >= 0)
    {
        path.push_back(current);
        current = previous[current.first][current.second];
    }
    for (std::vector<Vertex>::const_reverse_iterator iter = path.rbegin(); iter != path.rend(); ++iter)
    {
        std::cout << iter->first + 1 << ' ' << iter->second + 1 << '\n';
    }
}