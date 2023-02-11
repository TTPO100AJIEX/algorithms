#pragma once

#include <vector>
#include "./utils/countOps.h"
#include "./utils/swap.h"

#ifdef COUNT_ELEMENTARY_OPERATIONS
    extern unsigned int elementaryOperations;
#endif

static void bubbleDown(std::vector<unsigned int>& data, unsigned int index, unsigned int size)
{
    const unsigned int leftIndex = (index << 1) + 1, rightIndex = (index << 1) + 2;
    unsigned int swapWith = size;
    if (leftIndex < size && data[index] < data[leftIndex]) swapWith = leftIndex;
    if (rightIndex < size && data[index] < data[rightIndex] && data[leftIndex] < data[rightIndex]) swapWith = rightIndex;
    if (swapWith == size) return;
    swap(data[index], data[swapWith]);
    bubbleDown(data, swapWith, size);
}

void sort(std::vector<unsigned int>& data)
{
    for (int i = data.size() - 1; i >= 0; --i) bubbleDown(data, i, data.size());
    unsigned int unsortedSize = data.size();
    while (unsortedSize > 1) { --unsortedSize; swap(data[0], data[unsortedSize]); bubbleDown(data, 0, unsortedSize); }
}