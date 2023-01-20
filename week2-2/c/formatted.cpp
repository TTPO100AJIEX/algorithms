#include <iostream>
#include <ios>
#include <vector>

struct Drone {
    unsigned int id;
    unsigned int weight;
};
void radixSort(std::vector<Drone>& data) {
    for (unsigned int digit = 0; digit < 4; digit++) {
        std::vector<Drone> counter[256];
        for (unsigned int i = 0; i < data.size(); i++) {
            const unsigned int offset = (digit << 3);
            const unsigned int digit_value = (data[i].weight & (255 << offset)) >> offset;
            counter[digit_value].push_back(data[i]);
        }
        for (int i = 255, cur_index = 0; i >= 0; i--) {
            for (unsigned int j = 0; j < counter[i].size(); j++) {
                data[cur_index++] = counter[i][j];
            }
        }
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned int n;
    std::cin >> n;
    std::vector<Drone> data(n);
    for (unsigned int i = 0; i < n; i++) {
        std::cin >> data[i].id >> data[i].weight;
    }
    radixSort(data);
    for (unsigned int i = 0; i < n; i++) {
        std::cout << data[i].id << "   " << data[i].weight << "\n";
    }
    return 0;
}