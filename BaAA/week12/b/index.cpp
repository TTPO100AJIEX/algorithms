#include <ios>
#include <iostream>
#include <vector>
#include <set>

std::vector< std::vector <unsigned int> > edges;
std::vector< std::vector <unsigned int> > edges_transposed;
std::vector<bool> used;
std::vector<unsigned int> order;
unsigned int componentNumber = 0;
std::vector<unsigned int> components;
std::vector<unsigned int> component;

void dfs1(unsigned int vertex)
{
    if (used[vertex]) return;
    used[vertex] = true;
    for (unsigned int sibling : edges[vertex]) dfs1(sibling);
    order.push_back(vertex);
}

void dfs2(unsigned int vertex)
{
    if (components[vertex] != (1 << 30)) return;
    components[vertex] = componentNumber;
    component.push_back(vertex);
    for (unsigned int sibling : edges_transposed[vertex]) dfs2(sibling);
}

std::vector< std::set<unsigned int> > componentEdges;
std::vector<unsigned int> componentUsed;
void dfs3(unsigned int vertex, unsigned int level = 1)
{
    if (componentUsed[vertex] != 0)
    {
        componentUsed[vertex] = std::max(componentUsed[vertex], level);
        return;
    }
    componentUsed[vertex] = std::max(componentUsed[vertex], level);
    for (unsigned int sibling : componentEdges[vertex]) dfs3(sibling, level + 1);
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

    components.resize(n, (1 << 30));
    std::vector< std::pair<unsigned int, unsigned int> > answer;
    for (unsigned int i = 0; i < n; ++i)
    {
        if (components[order[n - i - 1]] != (1 << 30)) continue;
        component.clear();
        dfs2(order[n - i - 1]);
        ++componentNumber;
        if (component.size() == 1) continue;
        for (unsigned int i = 0; i < component.size() - 1; ++i) answer.emplace_back(component[i], component[i + 1]);
        answer.emplace_back(component[component.size() - 1], component[0]);
    }
    
    componentEdges.resize(componentNumber);
    std::vector<unsigned int> componentVertex(componentNumber, (1 << 30));
    for (unsigned int vertex = 0; vertex < n; ++vertex)
    {
        for (unsigned int sibling : edges[vertex])
        {
            if (components[vertex] == components[sibling]) continue;
            componentEdges[components[vertex]].insert(components[sibling]);
            componentVertex[components[vertex]] = vertex;
            componentVertex[components[sibling]] = sibling;
        }
    }

    componentUsed.resize(componentNumber);
    for (unsigned int i = 0; i < componentNumber; ++i)
    {
        std::fill(componentUsed.begin(), componentUsed.end(), 0);
        dfs3(i);
        for (std::set<unsigned int>::iterator iter = componentEdges[i].begin(); iter != componentEdges[i].end(); )
        {
            if (componentUsed[*iter] > 2) iter = componentEdges[i].erase(iter);
            else ++iter;
        }
    }


    for (unsigned int i = 0; i < componentNumber; ++i)
    {
        for (unsigned int j : componentEdges[i]) answer.emplace_back(componentVertex[i], componentVertex[j]);
    }

    std::cout << answer.size() << '\n';
    for (const std::pair<unsigned int, unsigned int>& edge : answer) std::cout << edge.first + 1 << ' ' << edge.second + 1 << '\n';
}