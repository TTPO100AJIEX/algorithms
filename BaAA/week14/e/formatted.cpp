#include <ios>
#include <iostream>
#include <cstdint>
#include <climits>
#include <queue>
#include <vector>
#include <utility>
#include <functional>

unsigned int getSumDigits(uint16_t number) {
    unsigned int answer = 0;
    while (number > 0) {
        answer += (number % 10);
        number /= 10;
    }
    return answer;
}

void printPath(const std::vector<uint16_t>& parents, uint16_t vertex, uint16_t dist = 0) {
    if (parents[vertex] == 0) {
        std::cout << dist << '\n';
        return;
    }
    printPath(parents, parents[vertex], dist + 1);
    int16_t operation = vertex - parents[vertex];
    if (operation > 0) {
        std::cout << '+';
    }
    std::cout << operation << '\n';
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    uint16_t n, a, b;
    std::cin >> n >> a >> b;
    ++n;

    constexpr unsigned int kInf = UINT_MAX;
    std::vector<uint16_t> parents(n, 0);
    std::vector<unsigned int> distances(n, kInf);
    distances[a] = 0;

    using Result = std::pair<unsigned int, uint16_t>;
    std::priority_queue<Result, std::vector<Result>, std::greater<Result>> to_update;
    to_update.emplace(0, a);
    while (!to_update.empty()) {
        const auto [current_distance, from] = to_update.top();
        if (from == b) {
            std::cout << current_distance << '\n';
            printPath(parents, b);
            return 0;
        }
        to_update.pop();

        uint16_t prefix = from;
        while (prefix > 0) {
            uint16_t suffix = prefix;
            unsigned int power10 = 1;
            do {
                uint16_t y = suffix % (power10 *= 10);
                unsigned int attempt_distance = current_distance + getSumDigits(y);
                if (from + y < n && attempt_distance < distances[from + y]) {
                    distances[from + y] = attempt_distance;
                    parents[from + y] = from;
                    to_update.emplace(attempt_distance, from + y);
                }
                if (from != y && attempt_distance < distances[from - y]) {
                    distances[from - y] = attempt_distance;
                    parents[from - y] = from;
                    to_update.emplace(attempt_distance, from - y);
                }
            } while (suffix % power10 != prefix);
            prefix /= 10;
        }
    }

    std::cout << -1;
}