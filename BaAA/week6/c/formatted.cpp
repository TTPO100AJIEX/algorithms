#include <ios>
#include <iostream>
#include <cstdint>
#include <utility>
#include <algorithm>
#include <vector>

constexpr uint64_t kMaxLevel = 2000000;
constexpr uint64_t kModulus = 1000000007;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<std::pair<uint64_t, uint64_t> > answers(kMaxLevel + 1);

    answers[0] = {0, 0};
    answers[1] = {0, 0};
    for (unsigned int i = 2; i <= kMaxLevel; ++i) {
        answers[i].first = (answers[i - 1].second + 2 * answers[i - 2].second + 4) % kModulus;
        answers[i].second = (std::max(answers[i - 1].first, answers[i - 1].second) +
                             2 * std::max(answers[i - 2].first, answers[i - 2].second)) %
                            kModulus;
    }

    unsigned int n;
    std::cin >> n;
    for (unsigned int i = 0; i < n; ++i) {
        unsigned int index;
        std::cin >> index;
        --index;
        std::cout << std::max(answers[index].first, answers[index].second) << "\n";
    }
}
