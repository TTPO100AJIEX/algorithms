#include <ios>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int main() {
    std::string x, y;
    std::cin >> x >> y;
    if (x.empty() || y.empty()) {
        std::cout << 0;
        return 0;
    }
    std::vector<std::vector<int> > counter(x.size() + 1, std::vector<int>(y.size() + 1, 0));
    for (unsigned int i = 1; i <= x.size(); i++) {
        for (unsigned int j = 1; j <= y.size(); j++) {
            if (x[i - 1] == y[j - 1]) {
                counter[i][j] = counter[i - 1][j - 1] + 1;
            } else {
                counter[i][j] = std::max(counter[i - 1][j], counter[i][j - 1]);
            }
        }
    }
    std::cout << counter[x.size()][y.size()];
    return 0;
}