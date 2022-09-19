#include <iostream>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, max_divide = 0, sum = 0, number = 0, divide = 0;
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        std::cin >> number;
        number = abs(number);
        if (number == 0) {
            continue;
        }
        sum++;
        while (number != 1) {
            sum += (number & 1);
            number >>= 1;
            divide++;
        }
        if (divide > max_divide) {
            max_divide = divide;
        }
        divide = 0;
    }
    std::cout << max_divide + sum;

    return 0;
}