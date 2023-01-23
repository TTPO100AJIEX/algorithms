#include <iostream>
#include <ios>
#include <vector>

#define VALUE_LIMIT 1000000000

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned int n;
    std::cin >> n;
    std::vector<int> data(n);
    for (unsigned int i = 0; i < n; i++) {
        std::cin >> data[i];
        data[i] += VALUE_LIMIT;
    }

    for (unsigned int digit = 0; digit < 4; digit++) {
        const unsigned int offset = (digit << 3);
        std::vector<int> counter[256];
        for (unsigned int i = 0; i < n; i++) {
            const unsigned int digit_value = (data[i] >> offset) & 255;
            counter[digit_value].push_back(data[i]);
        }
        for (unsigned int i = 0, cur_index = 0; i < 256; i++) {
            for (unsigned int j = 0; j < counter[i].size(); j++) {
                data[cur_index++] = counter[i][j];
            }
        }
    }

    for (unsigned int i = 0; i < n; i++) {
        std::cout << data[i] - VALUE_LIMIT << " ";
    }
    return 0;
}