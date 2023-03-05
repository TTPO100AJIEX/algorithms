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
    std::sort(items.begin(), items.end());

    unsigned int sum_weiht = 0;
    uint64_t sum_price = 0;
    std::vector<Item> taken_items;
    for (const Item& item : items) {
        if (item.weight <= w) {
            sum_weiht += item.weight;
            sum_price += item.price;
            taken_items.push_back(item);
            w -= item.weight;
        }
    }

    std::cout << sum_price << "\n" << sum_weiht << "\n" << taken_items.size() << "\n";
    for (const Item& item : taken_items) {
        std::cout << item.weight << " ";
    }
    std::cout << "\n";
    for (const Item& item : taken_items) {
        std::cout << item.price << " ";
    }
}