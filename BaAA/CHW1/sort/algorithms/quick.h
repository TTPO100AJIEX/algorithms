#pragma once

#include <vector>
#include "./utils/countOps.h"
#include "./utils/swap.h"


void sort(std::vector<unsigned int>& data, unsigned int left, unsigned int right)
{
    countOps(4); // access left, access right, sum, compare
    if (right < left + 2) return;

    countOps(3); // access left, access data[left], create and initialize pivot
    countOps(3); // access right, subtract 1, create and initialize firstLower
    unsigned int pivot = data[left], firstLower = right - 1;
    countOps(2); // access firstLower, create and initialize i
    countOps(3); // access i, access left, compare
    for (unsigned int i = firstLower; i > left; --i)
    {
        countOps(4); // access i, access data[i], access pivot, compare
        if (data[i] <= pivot) continue;
        countOps(2); // access i, access firstLower
        swap(data[i], data[firstLower]);
        countOps(3); // access firstLower, decrement firstLower, assign firstLower
        firstLower--;
        countOps(3); // access i, decrement i, assign i
        countOps(3); // access i, access left, compare
    }
    countOps(2); // access firstLower, access left
    swap(data[firstLower], data[left]);
    sort(data, left, firstLower);
    countOps(2); // access firstLower, add
    sort(data, firstLower + 1, right);
}

void sort(std::vector<unsigned int>& data)
{
    sort(data, 0, data.size());
}