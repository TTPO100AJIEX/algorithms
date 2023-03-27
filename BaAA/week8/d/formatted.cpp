#include <ios>
#include <iostream>
#include <cmath>
#include <string>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string encoded;
    std::cin >> encoded;

    const unsigned int syndrome_size = static_cast<int>(log2(encoded.size())) + 1;
    std::vector<bool> syndrome(syndrome_size, 0);
    for (unsigned int i = 0; i < encoded.size(); ++i) {
        if (encoded[i] == '0') {
            continue;
        }
        unsigned int column = i + 1, bit_number = 0;
        while (column > 0) {
            if (column % 2 == 1) {
                syndrome[bit_number] = !syndrome[bit_number];
            }
            column /= 2;
            ++bit_number;
        }
    }

    unsigned error_bit = 0;
    for (unsigned int i = 0; i < syndrome_size; ++i) {
        if (syndrome[i]) {
            error_bit += (1 << i);
        }
    }
    if (error_bit != 0) {
        if (encoded[error_bit - 1] == '0') {
            encoded[error_bit - 1] = '1';
        } else {
            encoded[error_bit - 1] = '0';
        }
    }

    for (unsigned int i = 0; i < encoded.size(); ++i) {
        if ((i & (i + 1)) == 0) {
            continue;
        }
        std::cout << encoded[i];
    }
}