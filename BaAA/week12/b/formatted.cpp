#include <ios>
#include <iostream>
#include <vector>
#include <set>

std::vector<std::vector<unsigned int> > edges;
std::vector<std::vector<unsigned int> > edges_transposed;
std::vector<bool> used;
std::vector<unsigned int> order;
unsigned int component_number = 0;
std::vector<unsigned int> components;
std::vector<unsigned int> component;

void dfs1(unsigned int vertex) {
    if (used[vertex]) {
        return;
    }
    used[vertex] = true;
    for (unsigned int sibling : edges[vertex]) {
        dfs1(sibling);
    }
    order.push_back(vertex);
}

void dfs2(unsigned int vertex) {
    if (components[vertex] != (1 << 30)) {
        return;
    }
    components[vertex] = component_number;
    component.push_back(vertex);
    for (unsigned int sibling : edges_transposed[vertex]) {
        dfs2(sibling);
    }
}

std::vector<std::set<unsigned int> > component_edges;
std::vector<unsigned int> component_used;
void dfs3(unsigned int vertex, unsigned int level = 1) {
    if (component_used[vertex] != 0) {
        component_used[vertex] = std::max(component_used[vertex], level);
        return;
    }
    component_used[vertex] = std::max(component_used[vertex], level);
    for (unsigned int sibling : component_edges[vertex]) {
        dfs3(sibling, level + 1);
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned int n, m;
    std::cin >> n >> m;
    edges.resize(n);
    edges_transposed.resize(n);
    for (unsigned int i = 0; i < m; ++i) {
        unsigned int from, to;
        std::cin >> from >> to;
        --from;
        --to;
        edges[from].push_back(to);
        edges_transposed[to].push_back(from);
    }

    used.resize(n, false);
    order.reserve(n);
    for (unsigned int i = 0; i < n; ++i) {
        dfs1(i);
    }

    components.resize(n, (1 << 30));
    std::vector<std::pair<unsigned int, unsigned int> > answer;
    for (unsigned int i = 0; i < n; ++i) {
        if (components[order[n - i - 1]] != (1 << 30)) {
            continue;
        }
        component.clear();
        dfs2(order[n - i - 1]);
        ++component_number;
        if (component.size() == 1) {
            continue;
        }
        for (unsigned int i = 0; i < component.size() - 1; ++i) {
            answer.emplace_back(component[i], component[i + 1]);
        }
        answer.emplace_back(component[component.size() - 1], component[0]);
    }

    component_edges.resize(component_number);
    std::vector<unsigned int> component_vertex(component_number, (1 << 30));
    for (unsigned int vertex = 0; vertex < n; ++vertex) {
        for (unsigned int sibling : edges[vertex]) {
            if (components[vertex] == components[sibling]) {
                continue;
            }
            component_edges[components[vertex]].insert(components[sibling]);
            component_vertex[components[vertex]] = vertex;
            component_vertex[components[sibling]] = sibling;
        }
    }

    component_used.resize(component_number);
    for (unsigned int i = 0; i < component_number; ++i) {
        std::fill(component_used.begin(), component_used.end(), 0);
        dfs3(i);
        for (std::set<unsigned int>::iterator iter = component_edges[i].begin();
             iter != component_edges[i].end();) {
            if (component_used[*iter] > 2) {
                iter = component_edges[i].erase(iter);
            } else {
                ++iter;
            }
        }
    }

    for (unsigned int i = 0; i < component_number; ++i) {
        for (unsigned int j : component_edges[i]) {
            answer.emplace_back(component_vertex[i], component_vertex[j]);
        }
    }

    std::cout << answer.size() << '\n';
    for (const std::pair<unsigned int, unsigned int>& edge : answer) {
        std::cout << edge.first + 1 << ' ' << edge.second + 1 << '\n';
    }
}