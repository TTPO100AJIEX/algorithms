#include <iostream>
#include <cmath>

int main(void) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;
    if (n == 0) {
        std::cout << "0";
        return 0;
    }
    while (n != 0) {
        int res = sqrt(n);
        std::cout << res << " ";
        n -= res * res;
    }

    return 0;
}