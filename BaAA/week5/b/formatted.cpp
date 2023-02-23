#include <ios>
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned int n, w;
    std::cin >> n >> w;
    if (w == 0) {
        std::cout << "0\n0";
        return 0;
    }

    std::vector<unsigned int> weights(n);
    for (unsigned int i = 0; i < n; i++) {
        std::cin >> weights[i];
    }

    std::vector<std::vector<unsigned int> > dp(n + 1, std::vector<unsigned int>(w + 1, 0));
    for (unsigned int i = 1; i <= n; i++) {
        for (unsigned int j = 1; j <= w; j++) {
            if (j >= weights[i - 1]) {
                dp[i][j] = std::max(dp[i - 1][j], dp[i - 1][j - weights[i - 1]] + weights[i - 1]);
            } else {
                dp[i][j] = dp[i - 1][j];
            }
        }
    }
    std::cout << dp[n][w] << "\n";

    std::vector<unsigned int> ans;
    unsigned int cur_i = n, cur_j = w;
    while (cur_i != 0) {
        if (dp[cur_i][cur_j] == dp[cur_i - 1][cur_j]) {
            cur_i--;
        } else {
            ans.push_back(weights[cur_i - 1]);
            cur_j -= weights[--cur_i];
        }
    }
    std::sort(ans.begin(), ans.end());
    std::cout << ans.size() << "\n";
    for (unsigned int i = 0; i < ans.size(); i++) {
        std::cout << ans[i] << " ";
    }
}