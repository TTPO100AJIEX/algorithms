#pragma once

#include <vector>
#include "./utils/countOps.h"
#include "./utils/swap.h"


static void bubbleDown(std::vector<unsigned int>& data, unsigned int index, unsigned int size)
{
    countOps(4); // access index, binary shift, add 1, create and initialize leftIndex
    countOps(4); // access index, binary shift, add 2, create and initialize rightIndex
    const unsigned int leftIndex = (index << 1) + 1, rightIndex = (index << 1) + 2;
    countOps(2); // access size, create and initialize swapWith
    unsigned int swapWith = size;
    countOps(8); // access leftIndex, access size, access index, access data[index], access data[leftIndex], compare x2, logical and
    if (leftIndex < size && data[index] < data[leftIndex])
    {
        countOps(2); // access leftIndex, assign
        swapWith = leftIndex;
    }
    countOps(12); // access rightIndex, access size, access index, access leftIndex, access data[index], access data[rightIndex], access data[leftIndex], compare x3, logical and x2
    if (rightIndex < size && data[index] < data[rightIndex] && data[leftIndex] < data[rightIndex])
    {
        countOps(2); // access rightIndex, assign
        swapWith = rightIndex;
    }
    countOps(3); // access swapWith, access size, compare
    if (swapWith == size) return;
    countOps(2); // access index, access swapWith
    swap(data[index], data[swapWith]);
    bubbleDown(data, swapWith, size);
}

void sort(std::vector<unsigned int>& data)
{
    countOps(3); // access size, subtract 1, create and initialize i
    countOps(2); // access i, compare
    for (int i = data.size() - 1; i >= 0; --i)
    {
        bubbleDown(data, i, data.size());
        countOps(2); // access i, compare
        countOps(3); // access i, decrement i, assign i
        countOps(2); // access i, compare
    }
    countOps(3); // access size, create and initialize i
    unsigned int unsortedSize = data.size();
    countOps(2); // access unsortedSize, compare
    while (unsortedSize > 1)
    {
        countOps(3); // access unsortedSize, decrement unsortedSize, assign unsortedSize
        --unsortedSize;
        countOps(1); // access unsortedSize
        swap(data[0], data[unsortedSize]);
        bubbleDown(data, 0, unsortedSize);
        countOps(2); // access unsortedSize, compare
    }
}