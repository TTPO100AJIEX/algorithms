#include <ios>
#include <iostream>
#include <climits>
#include <set>
#include <vector>
#include <utility>

unsigned int getSumDigits(unsigned int number)
{
    unsigned int answer = 0;
    while (number > 0)
    {
        answer += (number % 10);
        number /= 10;
    }
    return answer;
}

void printPath(const std::vector<unsigned int>& parents, unsigned int vertex, unsigned int dist = 0)
{
    if (parents[vertex] == 0) { std::cout << dist << '\n'; return; }
    printPath(parents, parents[vertex], dist + 1);
    int16_t operation = vertex - parents[vertex];
    if (operation > 0) std::cout << '+';
    std::cout << operation << '\n';
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned int n, a, b;
    std::cin >> n >> a >> b;
    ++n;

    constexpr unsigned int INF = UINT_MAX;
    std::vector<unsigned int> parents(n, 0);
    std::vector<unsigned int> distances(n, INF);
    distances[a] = 0;

    std::set< std::pair<unsigned int, unsigned int> > to_update;
    to_update.emplace(0, a);
    while (!to_update.empty())
    {
        auto [ current_distance, from ] = *(to_update.begin());
        if (from == b)
        {
            std::cout << current_distance << '\n';
            printPath(parents, b);
            return 0;
        }
        to_update.erase(to_update.begin());

        unsigned int prefix = from;
        while (prefix > 0)
        {
            unsigned int suffix = prefix;
            unsigned int power10 = 1;
            do
            {
                unsigned int y = suffix % (power10 *= 10);
                unsigned int attempt_distance = current_distance + getSumDigits(y);
                if (from + y < n && attempt_distance < distances[from + y])
                {
                    to_update.erase({ distances[from + y], from + y });
                    distances[from + y] = attempt_distance;
                    parents[from + y] = from;
                    to_update.emplace(attempt_distance, from + y);
                }
                if (from != y && attempt_distance < distances[from - y])
                {
                    to_update.erase({ distances[from - y], from - y });
                    distances[from - y] = attempt_distance;
                    parents[from - y] = from;
                    to_update.emplace(attempt_distance, from - y);
                }
            } while (suffix % power10 != prefix);
            prefix /= 10;
        }
    }

    std::cout << -1;
}