#include <iostream>
#include <algorithm>

unsigned int findMax(unsigned int left, unsigned int right, unsigned int secondMax = 0)
{
    std::cout << "&" << left << " " << right << std::endl;
    if (left == right) return left;
    if (secondMax == 0) { std::cout << "? " << left << " " << right << std::endl; std::cin >> secondMax; }
    if (right == left + 1)
    {
        if (secondMax == left) return right;
        else return left;
    }
    unsigned int mid = ((left + right) >> 1);
    if (secondMax <= mid)
    {
        std::cout << "? " << left << " " << mid << std::endl;
        unsigned int localSecondMax; std::cin >> localSecondMax;
        if (secondMax == localSecondMax) return findMax(left, mid, secondMax);
        else return findMax(std::max(secondMax, localSecondMax), right, std::max(secondMax, localSecondMax));
    }
    else
    {
        if (mid + 1 == right) return findMax(left, mid, 0);
        std::cout << "? " << mid + 1 << " " << right << std::endl;
        unsigned int localSecondMax; std::cin >> localSecondMax;
        if (secondMax == localSecondMax) return findMax(mid + 1, right, secondMax);
        else return findMax(std::min(secondMax, localSecondMax), mid, std::min(secondMax, localSecondMax));
    }
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    unsigned int n; std::cin >> n;
    unsigned int ans = findMax(1, n);
    std::cout << "! " << ans << std::endl;
}