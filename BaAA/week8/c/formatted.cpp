#include <ios>
#include <iostream>
#include <cmath>
#include <string>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string data;
    std::cin >> data;
    std::string encoded = "0";
    for (unsigned int i = 0, next = 2; i < data.size(); ++i) {
        if (encoded.size() == next - 1) {
            encoded += '0';
            next *= 2;
        }
        encoded += data[i];
    }

    for (unsigned int i = 1; i < encoded.size(); ++i) {
        if (encoded[i] == '0' || (i & (i + 1)) == 0) {
            continue;
        }
        unsigned int column = i + 1, bit_number = 0;
        while (column > 0) {
            if (column % 2 == 1) {
                unsigned int index = (1 << bit_number) - 1;
                if (encoded[index] == '1') {
                    encoded[index] = '0';
                } else {
                    encoded[index] = '1';
                }
            }
            column /= 2;
            ++bit_number;
        }
    }

    std::cout << encoded;
}