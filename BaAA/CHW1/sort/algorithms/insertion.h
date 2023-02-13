#pragma once

#include <vector>
#include "./utils/countOps.h"


void sort(std::vector<unsigned int>& data)
{
    countOps(1); // create and initialize i
    countOps(3); // access i, access size, loop comparison
    for (unsigned int i = 1; i < data.size(); ++i) // Loop though input
    {
        countOps(3); // access i, access data[i], create and initialize pivot
        countOps(2); // access i, create and initialize j
        unsigned int pivot = data[i], j = i; 
        countOps(7); // access j, subtract 1, access data[j - 1], access pivot, compare x2, logical and
        for ( ; j > 0 && data[j - 1] > pivot; --j) // While current element should be moved to the left (is not in order)
        {
            countOps(4); // access j, subtract 1, access data[j - 1], assign
            data[j] = data[j - 1]; // Move the left element one position right
            countOps(3); // access j, decrement j, assign j
            countOps(7); // access j, subtract 1, access data[j - 1], access pivot, compare x2, logical and
        }
        countOps(2); // access pivot, assign
        data[j] = pivot; // Put current element where it should be
        countOps(3); // access i, increment i, assign i
        countOps(3); // access i, access size, loop comparison
    }
}