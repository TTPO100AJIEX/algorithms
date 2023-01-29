#include <ios>
#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>

void radixSort(std::vector<std::pair<unsigned int, bool> >& data) {
    std::vector<std::pair<unsigned int, bool> > res(data.size());
    for (unsigned int offset = 0; offset < 32; offset += 8) {
        unsigned int counter[256] = {0};
        for (unsigned int i = 0; i < data.size(); ++i) {
            ++counter[(data[i].first >> offset) & 255];
        }
        for (unsigned int i = 1; i < 256; ++i) {
            counter[i] += counter[i - 1];
        }
        for (int i = data.size() - 1; i >= 0; --i) {
            res[--counter[(data[i].first >> offset) & 255]] = data[i];
        }
        std::swap(data, res);
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    unsigned int n;
    std::cin >> n;
    std::vector<std::pair<unsigned int, bool> > events(2 * n);
    for (unsigned int i = 0; i < n; i++) {
        std::cin >> events[2 * i].first;
        events[2 * i].second = true;
        std::cin >> events[2 * i + 1].first;
        events[2 * i + 1].second = false;
    }
    radixSort(events);

    std::vector<std::tuple<unsigned int, unsigned int, unsigned int> > points;
    points.emplace_back(events[0].first, 1, 1);
    for (unsigned int i = 1; i < 2 * n; i++) {
        if (std::get<0>(points[points.size() - 1]) == events[i].first) {
            std::get<1>(points[points.size() - 1]) += (events[i].second ? 1 : -1);
            if (events[i].second) {
                std::get<2>(points[points.size() - 1])++;
            }
        } else {
            points.emplace_back(events[i].first, std::get<1>(points[points.size() - 1]),
                                std::get<1>(points[points.size() - 1]));
            i--;
        }
    }

    char command;
    std::cin >> command;
    while (command != '!') {
        unsigned int time;
        std::cin >> time;
        std::vector<std::tuple<unsigned int, unsigned int, unsigned int> >::iterator point =
            std::lower_bound(points.begin(), points.end(), time,
                             [](const std::tuple<unsigned int, unsigned int, unsigned int>& point,
                                unsigned int value) { return std::get<0>(point) < value; });
        if (point == points.end()) {
            std::cout << "! 0" << std::endl;
        } else {
            if (std::get<0>(*point) == time) {
                std::cout << "! " << std::get<2>(*point) << std::endl;
            } else {
                if (point == points.begin()) {
                    std::cout << "! 0" << std::endl;
                } else {
                    std::cout << "! " << std::get<1>(*(point - 1)) << std::endl;
                }
            }
        }

        std::cin >> command;
    }
}