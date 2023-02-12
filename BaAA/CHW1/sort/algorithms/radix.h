#pragma once

#include <vector>
#include "./utils/countOps.h"
#include "./utils/swap.h"


void sort(std::vector<unsigned int>& data)
{
    std::vector<unsigned int> res(data.size());
    countOps(1); // create and initialize offset
    countOps(2); // access offset, compare
    for (unsigned int offset = 0; offset < 16; offset += 8)
    {
        countOps(256); // create and initialize 256 variables for counter
        unsigned int counter[256] = { 0 };

        for (const unsigned int& item : data)
        {
            countOps(7); // access item, access offset, binary shift, binary and, access counter[...], increment counter[...], assign counter[...]
            ++counter[(item >> offset) & 255];
        }
        countOps(1); // create and initialize i
        countOps(2); // access i, compare
        for (unsigned int i = 1; i < 256; ++i)
        {
            countOps(4); // access i, subtract 1, access counter[i - 1], assign
            counter[i] += counter[i - 1];
            countOps(3); // access i, increment i, assign i
            countOps(2); // access i, compare
        }
        
        countOps(2); // access rbegin, create and initialize cur
        countOps(3); // access cur, access rend, compare
        for (std::vector<unsigned int>::reverse_iterator cur = data.rbegin(); cur != data.rend(); ++cur)
        {
            countOps(6); // access cur, access *cur, access offset, binary shift, binary and, access counter[...], decrement counter[...], assign counter[...], assign res[...]
            res[--counter[(*cur >> offset) & 255]] = *cur;
            countOps(3); // access cur, increment cur, assign cur
            countOps(3); // access cur, access rend, compare
        }
        swap(data, res);
        countOps(3); // access offset, increment offset, assign offset
        countOps(2); // access offset, compare
    }
}