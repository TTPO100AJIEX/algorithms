#pragma once

#include <vector>
#include "./utils/countOps.h"
#include "./utils/swap.h"


void sort(std::vector<unsigned int>& data)
{
    countOps(1); // create and initialize i
    countOps(4); // access i, access size, subtract, loop comparison
    for (unsigned int i = 0; i < data.size() - 1; ++i) // Loop through input
    {
        countOps(1); // create and initialize doContinue
        bool doContinue = false; // WFlag if there have been swaps on this iteration
        countOps(1); // create and initialize j
        countOps(6); // access j, access i, access size, subtract x2, loop comparison
        for (unsigned int j = 0; j < data.size() - i - 1; ++j) // Loop through the unsorted part of array
        {
            countOps(5); // access j, add 1, access data[j], access data[j + 1], comparison
            if (data[j] > data[j + 1]) // If the elements are not in order
            {
                countOps(2); // access j, add 1
                swap(data[j], data[j + 1]); // Swap the elements to put them in the correct order
                countOps(1); // assignment
                doContinue = true; // There has been a swap
            }
            countOps(3); // access j, increment j, assign j
            countOps(6); // access j, access i, access size, subtract x2, loop comparison
        }
        countOps(1); // comparison
        if (!doContinue) break; // We do not need to continue if there were no swaps
        countOps(3); // access i, increment i, assign i
        countOps(4); // access i, access size, subtract, loop comparison
    }
}