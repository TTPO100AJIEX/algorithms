#include <iostream>
#include <ios>
#include <vector>
#include <algorithm>

void countingSort(std::vector <int>& data)
{
    int min = 1e6, max = -1e6;
    for (unsigned int i = 0; i < data.size(); i++)
    {
        min = std::min(min, data[i]);
        max = std::max(max, data[i]);
    }
    unsigned int diff = max - min + 1;
    std::vector <unsigned int> counter(diff, 0);
    for (unsigned int i = 0; i < data.size(); i++) counter[data[i] - min]++;
    for (unsigned int i = 0, curIndex = 0; i < diff; i++)
    {
        for (unsigned int j = 0; j < counter[i]; j++) data[curIndex++] = i + min;
    }
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned int n; std::cin >> n;
    std::vector <int> data(n);
    for (unsigned int i = 0; i < n; i++) std::cin >> data[i];
    countingSort(data);
    for (unsigned int i = 0; i < n; i++) std::cout << data[i] << " ";
    return 0;
}