#include <ios>
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

enum class VisitedStatus : unsigned char { FALSE, VISITED, VISITING };
void tryToVisit(unsigned int current, std::vector<VisitedStatus>& visited,
                const std::vector<std::set<unsigned int> >& edges) {
    if (visited[current] != VisitedStatus::FALSE) {
        return;
    }
    visited[current] = VisitedStatus::VISITING;
    for (unsigned int sibling : edges[current]) {
        tryToVisit(sibling, visited, edges);
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned int n, k;
    std::cin >> n >> k;
    std::vector<VisitedStatus> visited(n, VisitedStatus::FALSE);
    visited[0] = VisitedStatus::VISITED;
    for (unsigned int i = 0; i < k; i++) {
        unsigned int amount;
        std::cin >> amount;
        std::vector<std::set<unsigned int> > edges(n);
        for (unsigned int j = 0; j < amount; j++) {
            unsigned int from, to;
            std::cin >> from >> to;
            from--;
            to--;
            edges[from].insert(to);
            edges[to].insert(from);
        }
        for (unsigned int i = 0; i < n; i++) {
            if (visited[i] == VisitedStatus::VISITED) {
                visited[i] = VisitedStatus::FALSE;
                tryToVisit(i, visited, edges);
            }
        }
        if (visited[n - 1] == VisitedStatus::VISITING) {
            std::cout << i + 1;
            return 0;
        }
        for (unsigned int i = 0; i < n; i++) {
            if (visited[i] == VisitedStatus::VISITING) {
                visited[i] = VisitedStatus::VISITED;
            }
        }
    }
    std::cout << -1;
    return 0;
}