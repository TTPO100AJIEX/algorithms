#include <ios>
#include <iostream>
#include <vector>
#include <algorithm>

struct State {
    unsigned int Connected;
    unsigned int NotConnected;
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned int n;
    std::cin >> n;
    std::vector<unsigned int> router_price(n);
    for (unsigned int i = 0; i < n; i++) {
        std::cin >> router_price[i];
    }

    State prev = {0, 0};
    for (unsigned int i = 0; i < n; i++) {
        unsigned int connect_price;
        if (i == 0) {
            connect_price = (1 << 31);
        } else {
            std::cin >> connect_price;
        }
        State cur;
        cur.Connected = std::min(prev.Connected + std::min(connect_price, router_price[i]),
                                 prev.NotConnected + connect_price + router_price[i]);
        cur.NotConnected = std::min(prev.Connected, prev.NotConnected + connect_price);
        prev = cur;
    }
    std::cout << prev.Connected;
}