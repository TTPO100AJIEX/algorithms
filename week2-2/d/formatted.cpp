#include <iostream>
#include <ios>
#include <vector>

#define SYMBOLS 'Z' - 'A' + 1

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned int n;
    std::cin >> n;
    std::vector<unsigned int> counter(SYMBOLS, 0);
    // unsigned int counter[SYMBOLS] = {[0 ... SYMBOLS - 1] = 0};
    for (unsigned int i = 0; i < n; i++) {
        char symbol;
        std::cin >> symbol;
        if (symbol < 'A' || symbol > 'Z') {
            i--;
            continue;
        }
        counter[symbol - 'A']++;
    }
    char center_symbol = 0;
    for (unsigned int i = 0; i < SYMBOLS; i++) {
        unsigned int half = (counter[i] >> 1);
        for (unsigned int j = 0; j < half; j++) {
            std::cout << static_cast<char>('A' + i);
        }
        if ((counter[i] & 1) == 1 && center_symbol == 0) {
            center_symbol = 'A' + i;
        }
        counter[i] = half;
    }
    if (center_symbol != 0) {
        std::cout << center_symbol;
    }
    for (int i = SYMBOLS - 1; i >= 0; i--) {
        for (unsigned int j = 0; j < counter[i]; j++) {
            std::cout << static_cast<char>('A' + i);
        }
    }
    return 0;
}