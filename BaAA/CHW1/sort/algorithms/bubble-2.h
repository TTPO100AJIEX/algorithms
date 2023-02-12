#pragma once

#include <vector>
#include "./utils/countOps.h"
#include "./utils/swap.h"


void sort(std::vector<unsigned int>& data)
{
    countOps(1); // create and initialize i
    countOps(3); // access size, subtract, create and initialize lastIndex
    countOps(7); // access lastIndex, compare lastIndex, access i, access size, substract, compare, logical and
    for (unsigned int i = 0, lastIndex = data.size() - 1; lastIndex != 0 && i < data.size() - 1; ++i)
    {
        countOps(1); // create and initialize savedLastIndex
        unsigned int savedLastIndex = lastIndex;
        countOps(1); // create and initialize j
        countOps(3); // access j, access savedLastIndex, compare
        for (unsigned int j = 0; j < savedLastIndex; ++j)
        {
            countOps(5); // access j, add 1, access data[j], access data[j + 1], comparison
            if (data[j] > data[j + 1])
            {
                countOps(2); // access j, add 1
                swap(data[j], data[j + 1]);
                countOps(2); // access j, assignment
                lastIndex = j;
            }
            countOps(3); // access j, increment j, assign j
            countOps(3); // access j, access savedLastIndex, compare
        }
        countOps(3); // access i, increment i, assign i
        countOps(7); // access lastIndex, compare lastIndex, access i, access size, substract, compare, logical and
    }
}