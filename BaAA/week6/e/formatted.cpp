#include <ios>
#include <iostream>
#include <cstdint>
#include <vector>
#include <algorithm>

struct Item {
    unsigned int weight;
    unsigned int price;

    bool operator<(const Item& other) {
        if (this->weight * other.price == other.weight * this->price) {
            return this->weight > other.weight;
        }
        return this->weight * other.price < other.weight * this->price;
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned int n, w;
    std::cin >> n >> w;
    std::vector<Item> items(n);
    for (unsigned int i = 0; i < n; ++i) {
        std::cin >> items[i].weight;
    }
    for (unsigned int i = 0; i < n; ++i) {
        std::cin >> items[i].price;
    }

    std::vector<std::vector<unsigned int> > dp(n + 1, std::vector<unsigned int>(w + 1, 0));
    for (unsigned int i = 1; i <= n; ++i) {
        unsigned int weight = items[i - 1].weight, price = items[i - 1].price;
        std::vector<unsigned int>& cur_dp = dp[i];
        std::vector<unsigned int>& prev_dp = dp[i - 1];
        for (unsigned int j = 1; j <= w; ++j) {
            if (j >= weight) {
                cur_dp[j] = std::max(prev_dp[j], prev_dp[j - weight] + price);
            } else {
                cur_dp[j] = prev_dp[j];
            }
        }
    }

    unsigned int sum_weight = 0;
    uint64_t sum_price = 0;
    std::vector<Item> taken_items;
    std::vector<Item>::reverse_iterator item_iter = items.rbegin();
    for (std::vector<std::vector<unsigned int> >::reverse_iterator now = dp.rbegin();
         now != dp.rend() - 1; ++now, ++item_iter) {
        if ((*now)[w] != (*(now + 1))[w]) {
            taken_items.push_back(*item_iter);
            w -= item_iter->weight;
            sum_weight += item_iter->weight;
            sum_price += item_iter->price;
        }
    }

    std::cout << sum_price << "\n" << sum_weight << "\n" << taken_items.size() << "\n";
    for (const Item& item : taken_items) {
        std::cout << item.weight << " ";
    }
    std::cout << "\n";
    for (const Item& item : taken_items) {
        std::cout << item.price << " ";
    }
}