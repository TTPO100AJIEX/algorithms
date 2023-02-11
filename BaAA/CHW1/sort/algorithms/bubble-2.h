#pragma once

#include <vector>
#include "./utils/countOps.h"
#include "./utils/swap.h"

#ifdef COUNT_ELEMENTARY_OPERATIONS
    extern unsigned int elementaryOperations;
#endif

void sort(std::vector<unsigned int>& data)
{
    for (unsigned int i = 0, lastIndex = data.size() - 1; lastIndex != 0 && i < data.size() - 1; ++i)
    {
        unsigned int savedLastIndex = lastIndex;
        for (unsigned int j = 0; j < savedLastIndex; ++j)
        {
            if (data[j] > data[j + 1]) { swap(data[j], data[j + 1]); lastIndex = j; }
        }
    }
}