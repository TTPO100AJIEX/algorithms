#pragma once

#include <vector>
#include "./utils/countOps.h"
#include "./utils/swap.h"

#ifdef COUNT_ELEMENTARY_OPERATIONS
    extern unsigned int elementaryOperations;
#endif

void sort(std::vector<unsigned int>& data, unsigned int left, unsigned int right)
{
    if (right < left + 2) return;

    unsigned int pivot = data[left], firstLower = right - 1;
    for (unsigned int i = right - 1; i > left; --i)
    {
        if (data[i] <= pivot) continue;
        swap(data[i], data[firstLower]);
        firstLower--;
    }
    swap(data[firstLower], data[left]);
    sort(data, left, firstLower);
    sort(data, firstLower + 1, right);
}

void sort(std::vector<unsigned int>& data)
{
    sort(data, 0, data.size());
}