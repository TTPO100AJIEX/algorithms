#include <ios>
#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned int n, l;
    std::cin >> l >> n;
    n += 2;
    std::vector <unsigned int> points(n);
    points[0] = 0; points[n - 1] = l;
    std::vector < std::vector <unsigned int> > dp(n, std::vector <unsigned int>(n, 0));
    for (unsigned int i = 1; i < n - 1; i++) std::cin >> points[i];
    
    for (int i = n - 1; i >= 0; i--)
    {
        for (unsigned int j = i + 1; j < n; j++)
        {
            unsigned int bestSplit = (unsigned int)(1 << 31);
            for (unsigned int splitpoint = i + 1; splitpoint < j; splitpoint++)
            {
                bestSplit = std::min(dp[i][splitpoint] + dp[splitpoint][j] + points[j] - points[i], bestSplit);
            }
            if (bestSplit != (unsigned int)(1 << 31)) dp[i][j] = bestSplit;
        }
    }
    std::cout << dp[0][n - 1];
}