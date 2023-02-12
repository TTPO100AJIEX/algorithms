#pragma once

#include <vector>
#include "./utils/countOps.h"
#include "./utils/swap.h"


void sort(std::vector<unsigned int>& data)
{
    countOps(2); // access begin, create and initialize cur
    countOps(4); // access cur, access end, subtract 1, compare
    for (std::vector<unsigned int>::iterator cur = data.begin(); cur != data.end() - 1; ++cur)
    {
        countOps(2); // access cur, create and initialize minimum
        std::vector<unsigned int>::iterator minimum = cur;
        countOps(3); // access cur, add 1, create and initialize minCur
        countOps(3); // access minCur, access end, compare
        for (std::vector<unsigned int>::iterator minCur = cur + 1; minCur != data.end(); ++minCur)
        {
            countOps(5); // access minCur, access *minCur, access minimum, access *minimum, compare
            if (*minCur < *minimum)
            {
                countOps(2); // access minCur, assign
                minimum = minCur;
            }
            countOps(3); // access minCur, increment minCur, assign minCur
            countOps(3); // access minCur, access end, compare
        }
        countOps(2); // access cur, access minimum
        swap(*cur, *minimum);
        countOps(3); // access cur, increment cur, assign cur
        countOps(4); // access cur, access end, subtract 1, compare
    }
}