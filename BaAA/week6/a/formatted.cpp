#include <ios>
#include <iostream>
#include <algorithm>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<char> > field(n + 2, std::vector<char>(m + 2, '!'));
    for (unsigned int i = 1; i <= n; ++i) {
        for (unsigned int j = 1; j <= m; ++j) {
            std::cin >> field[i][j];
        }
    }
    std::vector<std::vector<unsigned int> > max_square(n + 2, std::vector<unsigned int>(m + 2, 1));
    for (unsigned int i = 1; i <= n; ++i) {
        for (unsigned int j = 1; j <= m; ++j) {
            if (field[i][j] != field[i - 1][j - 1] || field[i][j] != field[i - 1][j] ||
                field[i][j] != field[i - 1][j + 1]) {
                continue;
            }
            unsigned int max = std::min(max_square[i - 1][j - 1],
                                        std::min(max_square[i - 1][j], max_square[i - 1][j + 1]));
            if (i > max + 1 && field[i][j] == field[i - max - 1][j]) {
                max_square[i][j] = max + 2;
            } else {
                max_square[i][j] = max;
            }
        }
    }

    unsigned int ans = 0;
    for (unsigned int i = 1; i <= n; ++i) {
        for (unsigned int j = 1; j <= m; ++j) {
            ans += (max_square[i][j] + 1) / 2;
        }
    }
    std::cout << ans;
}
