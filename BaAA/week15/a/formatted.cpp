#include <ios>
#include <iostream>
#include <cstdint>
#include <vector>
#include <algorithm>
#include <queue>

struct Edge {
    int64_t cur_flow;
    int64_t max_flow;
};
std::vector<std::vector<Edge> > edges;
std::vector<unsigned int> distances;
constexpr unsigned int kInf = (UINT32_MAX >> 1);

void findDistances(unsigned int from) {
    distances[from] = 0;
    std::queue<unsigned int> to_update;
    to_update.push(from);
    while (!to_update.empty()) {
        unsigned int updating = to_update.front();
        to_update.pop();
        for (unsigned int to = 0; to < edges.size(); to++) {
            if (edges[updating][to].cur_flow >= edges[updating][to].max_flow ||
                distances[to] <= distances[updating] + 1) {
                continue;
            }
            distances[to] = distances[updating] + 1;
            to_update.push(to);
        }
    }
}
int64_t findFlow(unsigned int from, unsigned int to, int64_t flow = (INT64_MAX >> 1)) {
    if (from == to || flow == 0) {
        return flow;
    }
    for (unsigned int i = 0; i < edges.size(); i++) {
        if (distances[i] != distances[from] + 1) {
            continue;
        }
        int64_t add_flow =
            findFlow(i, to, std::min(flow, edges[from][i].max_flow - edges[from][i].cur_flow));
        if (add_flow != 0) {
            edges[from][i].cur_flow += add_flow;
            edges[i][from].cur_flow -= add_flow;
            return add_flow;
        }
    }
    return 0;
}
int64_t maxFlow(unsigned int from, unsigned int to) {
    int64_t answer = 0;
    std::fill(distances.begin(), distances.end(), kInf);
    findDistances(from);
    while (distances[to] != kInf) {
        int64_t flow = findFlow(from, to);
        while (flow != 0) {
            answer += flow;
            flow = findFlow(from, to);
        }
        std::fill(distances.begin(), distances.end(), kInf);
        findDistances(from);
    }
    return answer;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned int n, m;
    std::cin >> n >> m;
    edges.resize(n, std::vector<Edge>(n, {0, 0}));
    distances.resize(n);
    for (unsigned int i = 0; i < m; i++) {
        unsigned int from, to;
        int64_t max_flow;
        std::cin >> from >> to >> max_flow;
        edges[from - 1][to - 1].max_flow = max_flow;
    }

    std::cout << maxFlow(0, n - 1);
}