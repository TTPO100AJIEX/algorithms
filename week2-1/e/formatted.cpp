#include <iostream>
#include <algorithm>

unsigned int findMax(unsigned int left, unsigned int right, unsigned int second_max = 0) {
    if (left == right) {
        return left;
    }
    if (second_max == 0) {
        std::cout << "? " << left << " " << right << std::endl;
        std::cin >> second_max;
    }
    if (right == left + 1) {
        if (second_max == left) {
            return right;
        } else {
            return left;
        }
    }
    unsigned int mid = ((left + right) >> 1);
    if (second_max <= mid) {
        std::cout << "? " << left << " " << mid << std::endl;
        unsigned int local_second_max;
        std::cin >> local_second_max;
        std::cout << "$" << second_max << " " << local_second_max << std::endl;
        if (second_max == local_second_max) {
            return findMax(left, mid, second_max);
        } else {
            return findMax(std::max(second_max, local_second_max), right,
                           std::max(second_max, local_second_max));
        }
    } else {
        if (mid + 1 == right) {
            return findMax(left, mid, 0);
        }
        std::cout << "? " << mid + 1 << " " << right << std::endl;
        unsigned int local_second_max;
        std::cin >> local_second_max;
        if (second_max == local_second_max) {
            return findMax(mid + 1, right, second_max);
        } else {
            return findMax(std::min(second_max, local_second_max), mid,
                           std::min(second_max, local_second_max));
        }
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned int n;
    std::cin >> n;
    unsigned int ans = findMax(1, n);
    std::cout << "! " << ans << std::endl;
}