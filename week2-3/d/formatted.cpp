#include <ios>
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

void radixSort(std::vector<std::pair<unsigned int, unsigned int> >& data) {
    std::vector<std::pair<unsigned int, unsigned int> > res(data.size());
    unsigned int counter[256] = {0};
    for (unsigned int offset = 0; offset < 32; offset += 8) {
        for (unsigned int i = 1; i < 256; ++i) {
            counter[i] = 0;
        }
        for (unsigned int i = 0; i < data.size(); ++i) {
            ++counter[(data[i].second >> offset) & 255];
        }
        for (unsigned int i = 1; i < 256; ++i) {
            counter[i] += counter[i - 1];
        }
        for (int i = data.size() - 1; i >= 0; --i) {
            res[--counter[(data[i].second >> offset) & 255]] = data[i];
        }
        std::swap(data, res);
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned int n;
    std::cin >> n;
    std::vector<std::pair<unsigned int, unsigned int> > villages(n);
    for (unsigned int i = 0; i < n; ++i) {
        villages[i].first = i;
        std::cin >> villages[i].second;
    }
    radixSort(villages);

    unsigned int m;
    std::cin >> m;
    std::vector<std::pair<unsigned int, unsigned int> > shelters(m);
    for (unsigned int i = 0; i < m; ++i) {
        shelters[i].first = i;
        std::cin >> shelters[i].second;
    }
    radixSort(shelters);

    for (unsigned int i = 0, nearest_left = 0; i < n; ++i) {
        while (nearest_left != m - 1 && shelters[nearest_left + 1].second < villages[i].second) {
            nearest_left++;
        }
        if (nearest_left == m - 1) {
            villages[i].second = shelters[nearest_left].first + 1;
            continue;
        }
        if (villages[i].second < shelters[nearest_left].second) {
            villages[i].second = shelters[nearest_left].first + 1;
            continue;
        }
        if (shelters[nearest_left + 1].second - villages[i].second <
            villages[i].second - shelters[nearest_left].second) {
            villages[i].second = shelters[nearest_left + 1].first + 1;
        } else {
            villages[i].second = shelters[nearest_left].first + 1;
        }
    }

    for (unsigned int i = 0; i < n;) {
        if (i == villages[i].first) {
            i++;
        } else {
            std::swap(villages[i], villages[villages[i].first]);
        }
    }
    for (unsigned int i = 0; i < n; ++i) {
        std::cout << villages[i].second << " ";
    }
}