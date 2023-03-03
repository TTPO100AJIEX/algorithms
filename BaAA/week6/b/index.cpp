#include <ios>
#include <iostream>
#include <cstdint>
#include <vector>

std::vector < std::vector <uint64_t> > cache;
uint64_t f(int i, int j, int n, int m)
{
    if (i == 0 && j == 0) return 1;
    if (i < 0 || j < 0 || i > n || j > m) return 0;
    if (cache[i][j] != 0) return cache[i][j];
    return cache[i][j] = f(i - 2, j + 1, n, m) + f(i - 2, j - 1, n, m) + f(i + 1, j - 2, n, m) + f(i - 1, j - 2, n, m);
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    unsigned int n, m; std::cin >> n >> m;
    cache.resize(n, std::vector <uint64_t>(m, 0));
    n--; m--; std::cout << f(n, m, n, m);
}
