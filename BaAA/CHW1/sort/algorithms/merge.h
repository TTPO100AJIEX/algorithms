#pragma once

#include <vector>
#include <algorithm>
#include "./utils/countOps.h"


void sort(std::vector<unsigned int>& data, unsigned int left, unsigned int right)
{
    countOps(4); // access left, access right, subtract, compare
    if (right - left == 1) return;

    countOps(5); // access left, access right, sum, binary shift, create and intialize breakpoint
    unsigned int breakpoint = (left + right) >> 1;
    sort(data, left, breakpoint);
    sort(data, breakpoint, right);

    std::vector <unsigned int> storage;
    storage.reserve(right - left);
    countOps(2); // access breakpoint, create and initialize saveBreakpoint
    countOps(2); // access left, create and initialize saveLeft
    unsigned int saveBreakpoint = breakpoint, saveLeft = left;
    countOps(7); // access left, access saveBreakpoint, access breakpoint, access right, compare x2, logical and
    while (left != saveBreakpoint && breakpoint != right)
    {
        countOps(5); // access left, access breakpoint, access data[left], access data[breakpoint], compare
        if (data[left] < data[breakpoint])
        {
            countOps(5); // access left, add 1, assign left, access data[left++], assign to storage[...]
            storage.push_back(data[left++]);
        }
        else
        {
            countOps(5); // access breakpoint, add 1, assign breakpoint, access data[breakpoint++], assign to storage[...]
            storage.push_back(data[breakpoint++]);
        }
        countOps(7); // access left, access saveBreakpoint, access breakpoint, access right, compare x2, logical and
    }
    countOps(3); // access left, access saveBreakpoint, compare
    while (left != saveBreakpoint)
    {
        countOps(5); // access left, add 1, assign left, access data[left++], assign to storage[...]
        storage.push_back(data[left++]);
        countOps(3); // access left, access saveBreakpoint, compare
    }
    countOps(3); // access breakpoint, access right, compare
    while (breakpoint != right)
    {
        countOps(5); // access breakpoint, add 1, assign breakpoint, access data[breakpoint++], assign to storage[...]
        storage.push_back(data[breakpoint++]);
        countOps(3); // access breakpoint, access right, compare
    }
    countOps(5); // access storage.begin, access storage.end, access data.begin, access saveLeft, sum
    countOps(2 * storage.size()); // in the RAM model it is just "access + assign" storage.size() times.
    std::copy(storage.begin(), storage.end(), data.begin() + saveLeft);
}

void sort(std::vector<unsigned int>& data)
{
    sort(data, 0, data.size());
}