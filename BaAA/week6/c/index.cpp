#include <ios>
#include <iostream>
#include <cstdint>
#include <utility>
#include <algorithm>
#include <vector>

constexpr uint64_t MAX_LEVEL = 2000000;
constexpr uint64_t MODULUS = 1000000007;

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector< std::pair <uint64_t, uint64_t> > answers(MAX_LEVEL + 1);

    answers[0] = { 0, 0 };
    answers[1] = { 0, 0 };
    for (unsigned int i = 2; i <= MAX_LEVEL; ++i)
    {
        answers[i].first = (answers[i - 1].second + 2 * answers[i - 2].second + 4) % MODULUS;
        answers[i].second = (std::max(answers[i - 1].first, answers[i - 1].second) + 2 * std::max(answers[i - 2].first, answers[i - 2].second)) % MODULUS;
    }

    unsigned int n; std::cin >> n;
    for (unsigned int i = 0; i < n; ++i)
    {
        unsigned int index; std::cin >> index; --index;
        std::cout << std::max(answers[index].first, answers[index].second) << "\n";
    }
}
