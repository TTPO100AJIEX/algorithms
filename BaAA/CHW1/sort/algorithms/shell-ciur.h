#pragma once

#include <vector>
#include "./utils/countOps.h"


static unsigned int CiurSequence[] = { 1750, 701, 301, 132, 57, 23, 10, 4, 1 }; // THe needed part of the sequence
void sort(std::vector<unsigned int>& data)
{
    for (const unsigned int& gap : CiurSequence) // Loop through gaps
    {
        // GAPPED INSERTION SORT
        countOps(2); // access gap, create and initialize i
        countOps(3); // access i, access size, compare
        for (unsigned int i = gap; i < data.size(); ++i) // Loop through input
        {
            countOps(3); // access i, access data[i], create and initialize pivot
            countOps(2); // access i, create and initialize j
            unsigned int pivot = data[i], j = i;
            countOps(8); // access j, access gap, subtract, access data[j - gap], access pivot, compare x2, logical and
            for ( ; j >= gap && data[j - gap] > pivot; j -= gap) // While current element should be moved to the left (is not in order)
            {
                countOps(5); // access j, access gap, subtract, access data[j - gap], assign
                data[j] = data[j - gap]; // Move the left element one position right
                countOps(4); // access j, access gap, subtract, assign j
                countOps(8); // access j, access gap, subtract, access data[j - gap], access pivot, compare x2, logical and
            }
            countOps(2); // access pivot, assign
            data[j] = pivot; // Put current element where it should be
            countOps(3); // access i, increment i, assign i
            countOps(3); // access i, access size, compare
        }
    }
}