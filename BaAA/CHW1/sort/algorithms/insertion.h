#pragma once

#include <vector>
#include "./utils/countOps.h"

#ifdef COUNT_ELEMENTARY_OPERATIONS
    extern unsigned int elementaryOperations;
#endif

void sort(std::vector<unsigned int>& data)
{
    for (unsigned int i = 1; i < data.size(); ++i)
    {
        unsigned int pivot = data[i], j = i;
        for ( ; j > 0 && data[j - 1] > pivot; --j) data[j] = data[j - 1];
        data[j] = pivot;
    }
}