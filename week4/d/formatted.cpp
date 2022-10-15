#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <climits>

int main(void) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<int> > data(n, std::vector<int>(m + 2));
    for (int i = 0; i < n; i++) {
        for (int j = 1; j <= m; j++) {
            std::cin >> data[i][j];
        }
        data[i][0] = INT_MIN;
        data[i][m + 1] = INT_MAX;
    }

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int left = 0, right = m + 1;
            while (right - left > 1) {
                int middle = (left + right) / 2;
                std::vector<int>::iterator first_higher =
                    std::lower_bound(data[j].begin(), data[j].end(), data[i][middle]);
                int dist = middle + std::distance(data[j].begin(), first_higher) - 1;
                if (dist >= m) {
                    right = middle;
                } else {
                    left = middle;
                }
            }
            std::vector<int>::iterator first_higher =
                std::lower_bound(data[j].begin(), data[j].end(), data[i][left]);
            int dist = left + std::distance(data[j].begin(), first_higher) - 1;
            int last_elem = data[i][left] == INT_MIN ? *(first_higher - 1) : data[i][left];
            left++;
            while (dist != m) {
                if (*first_higher < data[i][left]) {
                    last_elem = *(first_higher++);
                } else {
                    last_elem = data[i][left++];
                }
                dist++;
            }
            int sum = last_elem + std::min(*first_higher, data[i][left]);
            if (sum < 0) {
                std::cout << "-";
                sum = -sum;
            }
            if (sum % 2 == 1) {
                std::cout << sum / 2 << ".50000\n";
            } else {
                std::cout << sum / 2 << ".00000\n";
            }
        }
    }

    return 0;
}