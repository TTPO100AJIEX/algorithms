#include <iostream>
#include <algorithm>

struct Range {
    unsigned int left;
    unsigned int right;

    unsigned int length() {
        return this->right - this->left;
    }
};
unsigned int query(unsigned int left, unsigned int right) {
    if (left == right) {
        return 0;
    }
    std::cout << "? " << left << " " << right << std::endl;
    unsigned int ans;
    std::cin >> ans;
    return ans;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned int n;
    std::cin >> n;
    unsigned int pivot = query(1, n);
    unsigned int res = query(pivot, n);
    if (res == pivot) {
        Range answer = {pivot + 1, n};
        while (answer.length() != 0) {
            unsigned int mid = (answer.left + answer.right - 1) >> 1;
            res = query(pivot, mid);
            if (res == pivot) {
                answer.right = mid;
            } else {
                answer.left = mid + 1;
            }
        }
        std::cout << "! " << answer.left << std::endl;
    } else {
        Range answer = {1, pivot - 1};
        while (answer.length() != 0) {
            unsigned int mid = (answer.left + answer.right + 1) >> 1;
            res = query(mid, pivot);
            if (res == pivot) {
                answer.left = mid;
            } else {
                answer.right = mid - 1;
            }
        }
        std::cout << "! " << answer.left << std::endl;
    }
}