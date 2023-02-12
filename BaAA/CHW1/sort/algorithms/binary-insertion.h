#pragma once

#include <vector>
#include "./utils/countOps.h"
#include "./utils/swap.h"


void sort(std::vector<unsigned int>& data)
{
    countOps(1); // create and initialize i
    countOps(3); // access i, access size, loop comparison
    for (unsigned int i = 1; i < data.size(); ++i)
    {
        countOps(3); // access i, create and initialize left and right
        int left = -1, right = i;

        countOps(4); // access left, access right, subtract, loop comparison
        while (right - left > 1)
        {
            countOps(5); // access left, access right, sum, binary shift, create and initialize mid
            int mid = (left + right) >> 1;
            
            countOps(6); // access mid, access i, access data[mid], access data[i], comparison, assignment
            if (data[mid] > data[i]) right = mid;
            else left = mid;

            countOps(4); // access left, access right, subtract, loop comparison
        }

        countOps(2); // access i, create and initialize j
        countOps(3); // access j, access right, loop comparison
        for (unsigned int j = i; j > (unsigned int)(right); --j)
        {
            countOps(2); // access j, subtract 1
            swap(data[j], data[j - 1]);
            countOps(3); // access j, subtract from j, assign j
            countOps(3); // access j, access right, loop comparison
        }
        
        countOps(3); // access i, increment i, assign i
        countOps(3); // access i, access size, loop comparison
    }
}