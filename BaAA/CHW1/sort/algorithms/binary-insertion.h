#pragma once

#include <vector>
#include "./utils/countOps.h"
#include "./utils/swap.h"

#ifdef COUNT_ELEMENTARY_OPERATIONS
    extern unsigned int elementaryOperations;
#endif

void sort(std::vector<unsigned int>& data)
{
    countOps(2); // create and initialize i
    countOps(1); // loop comparison
    for (unsigned int i = 1; i < data.size(); ++i)
    {
        countOps(2 + 2); // create and initialize left and right
        int left = -1, right = i;

        countOps(1); // loop comparison
        while (right - left > 1)
        {
            countOps(2 + 2); // create and initialize mid + sum and binary shift
            int mid = (left + right) >> 1;
            
            countOps(2); // comparison + assignment
            if (data[mid] > data[i]) right = mid;
            else left = mid;

            countOps(1); // loop comparison
        }

        countOps(2); // create and initialize j
        countOps(1); // loop comparison
        for (unsigned int j = i; j > (unsigned int)(right); --j)
        {
            swap(data[j], data[j - 1]);
            countOps(2); // loop increment, loop comparison
        }
        
        countOps(2); // loop increment, loop comparison
    }
}