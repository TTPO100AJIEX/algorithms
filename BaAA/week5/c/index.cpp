#include <ios>
#include <iostream>
#include <vector>
#include <algorithm>

struct State
{
    unsigned int Connected;
    unsigned int NotConnected;
};

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unsigned int n;
    std::cin >>  n;
    std::vector <unsigned int> RouterPrice(n);
    for (unsigned int i = 0; i < n; i++) std::cin >> RouterPrice[i];

    State prev = { 0, 0 };
    for (unsigned int i = 0; i < n; i++)
    {
        unsigned int connectPrice;
        if (i == 0) connectPrice = (1 << 31);
        else std::cin >> connectPrice;
        State cur;
        cur.Connected = std::min(prev.Connected + std::min(connectPrice, RouterPrice[i]), prev.NotConnected + connectPrice + RouterPrice[i]);
        cur.NotConnected = std::min(prev.Connected, prev.NotConnected + connectPrice);
        prev = cur;
    }
    std::cout << prev.Connected;
}