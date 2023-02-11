#pragma once

#include <vector>
#include "./utils/countOps.h"
#include "./utils/swap.h"

#ifdef COUNT_ELEMENTARY_OPERATIONS
    extern unsigned int elementaryOperations;
#endif

void sort(std::vector<unsigned int>& data)
{
    for (unsigned int i = 0; i < data.size() - 1; i++)
    {
        for (unsigned int j = 0; j < data.size() - i - 1; j++)
        {
            if (data[j] > data[j + 1]) swap(data[j], data[j + 1]);
        }
    }
}