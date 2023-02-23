#include <ios>
#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>

struct Interval
{
    double left, right, weight;
};

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned int n;
    std::cin >> n;
    std::vector <Interval> intervals(n);
    for (unsigned int i = 0; i < n; i++) std::cin >> intervals[i].left >> intervals[i].right >> intervals[i].weight;
    std::sort(intervals.begin(), intervals.end(), [](const Interval& first, const Interval& second) { return first.right < second.right; });
    
    std::vector < std::pair <double, double> > dp(n + 1, { 0, 0 });
    for (unsigned int i = 1; i <= n; i++)
    {
        unsigned int left = i;
        while (left > 0 && intervals[left - 1].right > intervals[i - 1].left) left--;

        dp[i].first = std::max(dp[left].first, dp[left].second) + intervals[i - 1].weight;
        dp[i].second = std::max(dp[i - 1].first, dp[i - 1].second);
    }
    std::cout << std::fixed << std::setprecision(5) << std::max(dp[n].first, dp[n].second);
}