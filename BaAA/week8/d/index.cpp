#include <ios>
#include <iostream>
#include <cmath>
#include <string>
#include <vector>

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string encoded;
    std::cin >> encoded;
    
    const unsigned int syndromeSize = (int)(log2(encoded.size())) + 1;
    std::vector<bool> syndrome(syndromeSize, 0);
    for (unsigned int i = 0; i < encoded.size(); ++i)
    {
        if (encoded[i] == '0') continue;
        unsigned int column = i + 1, bitNumber = 0;
        while (column > 0)
        {
            if (column % 2 == 1)
            {
                syndrome[bitNumber] = !syndrome[bitNumber];
            }
            column /= 2;
            ++bitNumber;
        }
    }

    unsigned errorBit = 0;
    for (unsigned int i = 0; i < syndromeSize; ++i)
    {
        if (syndrome[i]) errorBit += (1 << i);
    }
    if (errorBit != 0 && errorBit <= encoded.size())
    {
        if (encoded[errorBit - 1] == '0') encoded[errorBit - 1] = '1';
        else encoded[errorBit - 1] = '0';
    }
    
    for (unsigned int i = 0; i < encoded.size(); ++i)
    {
        if ((i & (i + 1)) == 0) continue;
        std::cout << encoded[i];
    }
}