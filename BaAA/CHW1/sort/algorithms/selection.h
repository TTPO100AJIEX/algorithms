#pragma once

#include <vector>
#include "./utils/countOps.h"
#include "./utils/swap.h"

#ifdef COUNT_ELEMENTARY_OPERATIONS
    extern unsigned int elementaryOperations;
#endif

void sort(std::vector<unsigned int>& data)
{
    for (unsigned int i = 0; i < data.size() - 1; ++i)
    {
        unsigned int minIndex = i;
        for (unsigned int j = i + 1; j < data.size(); ++j)
        {
            if (data[j] < data[minIndex]) minIndex = j;
        }
        swap(data[i], data[minIndex]);
    }
}