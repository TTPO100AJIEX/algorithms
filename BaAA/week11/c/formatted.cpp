#include <ios>
#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>

std::vector<std::string> names;
bool personIndexComparator(const unsigned int first, const unsigned int second) {
    return names[first] < names[second];
}
std::vector<std::vector<unsigned int>> edges;

void print(unsigned int current) {
    if (names[current].empty()) {
        return;
    }
    std::cout << names[current] << '\n';
    names[current].clear();
    for (unsigned int sibling : edges[current]) {
        if (!names[sibling].empty()) {
            print(sibling);
        }
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned int n, m;
    std::cin >> n >> m;
    edges.resize(n);
    names.resize(n);
    for (unsigned int i = 0; i < n; ++i) {
        unsigned int index;
        std::cin >> index;
        std::cin.ignore(1);
        std::getline(std::cin, names[index]);
    }
    for (unsigned int i = 0; i < m; ++i) {
        unsigned int from, to;
        std::cin >> from >> to;
        edges[from].push_back(to);
        edges[to].push_back(from);
    }
    for (unsigned int i = 0; i < n; ++i) {
        std::sort(edges[i].begin(), edges[i].end(), personIndexComparator);
    }
    unsigned int number;
    std::cin >> number;
    print(number);
    return 0;
}