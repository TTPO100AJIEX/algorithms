#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

int main(void)
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned int n, m;
    std::cin >> n >> m;
    std::vector< std::vector<int> > data(n, std::vector<int>(m + 1));
    for (unsigned int i = 0; i < n; i++)
    {
        for (unsigned int j = 0; j < m; j++) std::cin >> data[i][j];
        data[i][m] = INT_MAX;
    }

    for (unsigned int i = 0; i < n; i++)
    {
        for (unsigned int j = i + 1; j < n; j++)
        {
            std::vector<int>::iterator iter1 = data[i].begin(), iter2 = data[j].begin();
            unsigned int taken = 0, last_elem = 0;
            while (taken != m)
            {
                if (*iter1 < *iter2) last_elem = *(iter1++);
                else last_elem = *(iter2++);
                taken++;
            }
            int sum = last_elem + std::min(*iter1, *iter2);
            if (sum < 0) { std::cout << "-"; sum = -sum; }
            if (sum % 2 == 1) std::cout << sum / 2 << ".50000\n";
            else std::cout << sum / 2 << ".00000\n";
        }
    }

    return 0;
}