#include <iostream>
#include <ios>
#include <vector>
#include <utility>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned int n;
    std::cin >> n;
    std::vector<std::pair<unsigned int, unsigned int> > data(n);
    for (unsigned int i = 0; i < n; i++) {
        std::cin >> data[i].first >> data[i].second;
    }

    for (unsigned int offset = 0; offset < 32; offset += 16) {
        std::vector<std::pair<unsigned int, unsigned int> > counter[65536];
        for (unsigned int i = 0; i < n; ++i) {
            counter[(data[i].second >> offset) & 65535].push_back(data[i]);
        }
        for (int i = 65535, cur_index = 0; i >= 0; i--) {
            for (unsigned int j = 0; j < counter[i].size(); ++j) {
                data[cur_index++] = std::move(counter[i][j]);
            }
        }
    }

    for (unsigned int i = 0; i < n; i++) {
        std::cout << data[i].first << "   " << data[i].second << "\n";
    }
    return 0;
}