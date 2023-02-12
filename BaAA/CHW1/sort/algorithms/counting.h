#pragma once

#include <vector>
#include "./utils/countOps.h"


void sort(std::vector<unsigned int>& data)
{
    countOps(1); // create and initialize max
    unsigned int max = 0;
    for (const unsigned int& item : data)
    {
        countOps(3); // access item, access max, compare
        if (item > max)
        {
            countOps(1); // assignment
            max = item;
        }
    }
    countOps(2); // access max, add 1
    countOps(max + 1); // create and initialize (max + 1) variables for counter
    countOps(1); // access size
    std::vector<unsigned int> counter(max + 1, 0), res(data.size());
    for (const unsigned int& item : data)
    {
        countOps(4); // access item, access counter[item], add 1, assign counter[item]
        ++counter[item];
    }
    countOps(3); // access begin, add 1, create and initialize it
    countOps(3); // access it, access end, compare
    for (std::vector<unsigned int>::iterator it = counter.begin() + 1; it != counter.end(); ++it)
    {
        countOps(6); // access it, access *it, subtract 1, access *(it - 1), sum, assign
        *it += *(it - 1);
        countOps(3); // access it, increment it, assign it
        countOps(3); // access it, access end, compare
    }
    countOps(2); // access rbegin, create and initialize cur
    countOps(3); // access cur, access rend, compare
    for (std::vector<unsigned int>::reverse_iterator cur = data.rbegin(); cur != data.rend(); ++cur)
    {
        countOps(6); // access cur, access *cur, access counter[*cur], subtract 1, assign, assign res[...]
        res[--counter[*cur]] = *cur;
        countOps(3); // access cur, increment cur, assign cur
        countOps(3); // access cur, access rend, compare
    }
    countOps(1); // assign
    data = res;
}