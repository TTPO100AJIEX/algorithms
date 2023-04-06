#include <ios>
#include <ostream>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>
#include <algorithm>

unsigned int lcs(std::string_view first, std::string_view second)
{
    if (first.size() == 0 || second.size() == 0) return 0;
    if (first.size() < second.size()) std::swap(first, second);

    static std::vector <unsigned int> dp(50, 0);
    std::fill(dp.begin(), dp.end(), 0);

    unsigned int ans = 0;
    for (unsigned int i = 0; i < first.size(); ++i)
    {
        unsigned int mem;
        for (unsigned int j = 0; j < second.size(); ++j)
        {
            if (first[i] == second[j])
            {
                if (i == 0 || j == 0)
                {
                    mem = dp[j];
                    dp[j] = 1;
                }
                else
                {
                    mem++;
                    std::swap(mem, dp[j]);
                }
                if (dp[j] > ans) ans = dp[j];
            }
            else
            {
                mem = dp[j];
                dp[j] = 0;
            }
        }
    }
    return ans;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cin.ignore(20, '\n');
    std::string ab_storage, ca_storage, bc_storage;
    std::cin >> ab_storage >> ca_storage >> bc_storage;
    std::string_view ab = std::string_view(ab_storage);
    std::string_view ca = std::string_view(ca_storage);
    std::string_view bc = std::string_view(bc_storage);
    unsigned int best_answer = 0;
    for (unsigned int i = 0; i <= ab.size(); ++i)
    {
        for (unsigned int j = 0; j <= ca.size(); ++j)
        {
            for (unsigned int x = 0; x <= bc.size(); ++x)
            {
                unsigned int answer = lcs(ab.substr(0, i), ca.substr(j)) + lcs(ab.substr(i), bc.substr(0, x)) + lcs(ca.substr(0, j), bc.substr(x));
                if (answer > best_answer)
                {
                    best_answer = answer;
                }
            }
        }
    }
    std::cout << best_answer;
}