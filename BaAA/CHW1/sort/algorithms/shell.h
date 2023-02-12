#pragma once

#include <vector>
#include "./utils/countOps.h"


void sort(std::vector<unsigned int>& data)
{
    countOps(3); // access size, binary shift, create and initialize gap
    countOps(2); // access gap, compare
    for (unsigned int gap = (data.size() >> 1); gap > 0; gap >>= 1)
    {
        countOps(2); // access gap, create and initialize i
        countOps(3); // access i, access size, compare
        for (unsigned int i = gap; i < data.size(); ++i)
        {
            countOps(3); // access i, access data[i], create and initialize pivot
            countOps(2); // access i, create and initialize j
            unsigned int pivot = data[i], j = i;
            countOps(8); // access j, access gap, subtract, access data[j - gap], access pivot, compare x2, logical and
            for ( ; j >= gap && data[j - gap] > pivot; j -= gap)
            {
                countOps(5); // access j, access gap, subtract, access data[j - gap], assign
                data[j] = data[j - gap];
                countOps(4); // access j, access gap, subtract, assign j
                countOps(8); // access j, access gap, subtract, access data[j - gap], access pivot, compare x2, logical and
            }
            countOps(2); // access pivot, assign
            data[j] = pivot;
            countOps(3); // access i, increment i, assign i
            countOps(3); // access i, access size, compare
        }
        countOps(3); // access gap, binary shift, assign gap
        countOps(2); // access gap, compare
    }
}