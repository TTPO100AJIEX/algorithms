#include <ios>
#include <iostream>
#include <cstdint>
#include <vector>
#include <algorithm>

struct Item
{
    unsigned int weight;
    unsigned int price;
};

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    unsigned int n, w;
    std::cin >> n >> w;
    std::vector <Item> items(n);
    for (unsigned int i = 0; i < n; ++i) std::cin >> items[i].weight;
    for (unsigned int i = 0; i < n; ++i) std::cin >> items[i].price;
    
    std::vector < std::vector<unsigned int> > dp(n + 1, std::vector<unsigned int>(w + 1, 0));
    for (unsigned int i = 1; i <= n; ++i)
    {
        unsigned int weight = items[i - 1].weight, price = items[i - 1].price;
        std::vector<unsigned int>& curDp = dp[i];
        std::vector<unsigned int>& prevDp = dp[i - 1];
        for (unsigned int j = 1; j <= w; ++j)
        {
            if (j >= weight) curDp[j] = std::max(prevDp[j], prevDp[j - weight] + price);
            else curDp[j] = prevDp[j];
        }
    }

    unsigned int sumWeight = 0;
    uint64_t sumPrice = 0;
    std::vector <Item> takenItems;
    std::vector <Item>::reverse_iterator itemIter = items.rbegin();
    for (std::vector < std::vector<unsigned int> >::reverse_iterator now = dp.rbegin(); now != dp.rend() - 1; ++now, ++itemIter)
    {
        if ((*now)[w] != (*(now + 1))[w])
        {
            takenItems.push_back(*itemIter);
            w -= itemIter->weight;
            sumWeight += itemIter->weight;
            sumPrice += itemIter->price;
        }
    }
    
    std::cout << sumPrice << "\n" << sumWeight << "\n" << takenItems.size() << "\n";
    for (const Item& item : takenItems) std::cout << item.weight << " ";
    std::cout << "\n";
    for (const Item& item : takenItems) std::cout << item.price << " ";
}