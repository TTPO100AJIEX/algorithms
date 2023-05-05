#include <ios>
#include <iostream>
#include <unordered_set>
#include <vector>
#include <iterator>

std::vector< std::vector <unsigned int> > edges;
std::vector< std::vector <unsigned int> > edges_transposed;
std::vector<bool> used;
std::vector<unsigned int> order;
unsigned int componentNumber = 0;
std::vector<unsigned int> components;

void dfs1(unsigned int vertex)
{
    if (used[vertex]) return;
    used[vertex] = true;
    for (unsigned int sibling : edges[vertex]) dfs1(sibling);
    order.push_back(vertex);
}

void dfs2(unsigned int vertex)
{
    if (components[vertex] != 0) return;
    components[vertex] = componentNumber;
    for (unsigned int sibling : edges_transposed[vertex]) dfs2(sibling);
}


int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned int n, m;
    std::cin >> n >> m;
    edges.resize(n);
    edges_transposed.resize(n);
    for (unsigned int i = 0; i < m; ++i)
    {
        unsigned int from, to;
        std::cin >> from >> to;
        --from; --to;
        edges[from].push_back(to);
        edges_transposed[to].push_back(from);
    }

    used.resize(n, false);
    order.reserve(n);
    for (unsigned int i = 0; i < n; ++i) dfs1(i);

    components.resize(n, 0);
    for (unsigned int i = 0; i < n; ++i)
    {
        if (components[order[n - i - 1]] != 0) continue;
        ++componentNumber;
        dfs2(order[n - i - 1]);
    }

    std::cout << componentNumber << '\n';
    for (unsigned int component : components) std::cout << component << ' ';
}