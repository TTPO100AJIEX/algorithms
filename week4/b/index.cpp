#include <iostream>
#include <unordered_map>
#include <cstdint>
#include <cmath>
#include <climits>

int main(void)
{
    //std::ios::sync_with_stdio(false);
    //std::cin.tie(nullptr);

    uint64_t a, b;
    std::cin >> a >> b;
    std::unordered_map<uint64_t, int64_t> divisors;

    uint64_t root_a = sqrt(a) + 1;
    for (uint64_t i = 2; i <= root_a; i++)
    {
        if (a % i == 0)
        {
            if (divisors.find(i) != divisors.end()) divisors[i]++;
            else divisors[i] = 1;
            a /= i;
            i--;
        }
    }
    if (a != 1)
    {
        if (divisors.find(a) != divisors.end()) divisors[a]++;
        else divisors[a] = 1;
    }
    
    uint64_t answer = 1;
    uint64_t root_b = sqrt(b) + 1;
    for (uint64_t i = 2; i <= root_b; i++)
    {
        if (b % i == 0)
        {
            if (divisors.find(i) != divisors.end())
            {
                if (divisors[i] > 0) answer *= i;
                divisors[i]--;
            }
            else divisors[i] = -1;
            b /= i;
            i--;
        }
    }
    if (b != 1)
    {
        if (divisors.find(b) != divisors.end())
        {
            if (divisors[b] > 0) answer *= b;
            divisors[b]--;
        }
        else divisors[b] = -1;
    }

    uint64_t ans1 = 1, ans2 = 1;
    for (auto it = divisors.begin(); it != divisors.end(); it++)
    {
        if (it->second < 0)
            ans1 = std::max(ans1, it->first);
        if (it->second > 0)
            ans2 = std::max(ans2, it->first);
    }
    std::cout << answer * std::max(ans1, ans2);

    return 0;
}