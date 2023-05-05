#include <ios>
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

std::vector< std::vector <unsigned int> > edges;
std::vector< std::vector <unsigned int> > edges_transposed;
std::vector<bool> used;
std::vector<unsigned int> order;
std::set<unsigned int> component;

void dfs1(unsigned int vertex)
{
    if (used[vertex]) return;
    used[vertex] = true;
    for (unsigned int sibling : edges[vertex]) dfs1(sibling);
    order.push_back(vertex);
}

void dfs2(unsigned int vertex)
{
    if (used[vertex]) return;
    used[vertex] = true;
    component.insert(vertex);
    for (unsigned int sibling : edges_transposed[vertex]) dfs2(sibling);
}


int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned int n, m, h;
    std::cin >> n >> m >> h;
    std::vector <unsigned int> hours(n);
    for (unsigned int i = 0; i < n; ++i) std::cin >> hours[i];
    
    edges.resize(n);
    edges_transposed.resize(n);
    for (unsigned int i = 0; i < m; ++i)
    {
        unsigned int from, to;
        std::cin >> from >> to;
        --from; --to;
        if (hours[from] == (hours[to] + 1) % h)
        {
            edges[to].push_back(from);
            edges_transposed[from].push_back(to);
        }
        if (hours[to] == (hours[from] + 1) % h)
        {
            edges[from].push_back(to);
            edges_transposed[to].push_back(from);
        }
    }

    used.resize(n, false);
    order.reserve(n);
    for (unsigned int i = 0; i < n; ++i) dfs1(i);

    std::fill(used.begin(), used.end(), false);
    std::set<unsigned int> answer;
    for (unsigned int i = 0; i < n; ++i)
    {
        component.clear();
        dfs2(order[n - i - 1]);

        if (component.size() == 0) continue;
        if (answer.size() != 0 && component.size() >= answer.size()) continue;
        bool isOk = true;
        for (unsigned int vertex : component)
        {
            for (unsigned int sibling : edges[vertex])
            {
                if (component.find(sibling) == component.end()) { isOk = false; break; }
            }
            if (!isOk) break;
        }
        if (isOk) std::swap(component, answer);
    }

    std::cout << answer.size() << '\n';
    for (unsigned int sibling : answer) std::cout << sibling + 1 << ' ';
}