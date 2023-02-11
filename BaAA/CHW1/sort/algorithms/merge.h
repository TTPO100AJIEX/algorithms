#pragma once

#include <vector>
#include "./utils/countOps.h"

#ifdef COUNT_ELEMENTARY_OPERATIONS
    extern unsigned int elementaryOperations;
#endif

void sort(std::vector<unsigned int>& data, unsigned int left, unsigned int right)
{
    if (right - left == 1) return;

    unsigned int breakpoint = (left + right) >> 1;
    sort(data, left, breakpoint);
    sort(data, breakpoint, right);

    std::vector <unsigned int> storage;
    storage.reserve(right - left);
    unsigned int saveBreakpoint = breakpoint, saveLeft = left;
    while (left != saveBreakpoint && breakpoint != right)
    {
        if (data[left] < data[breakpoint]) storage.push_back(data[left++]);
        else storage.push_back(data[breakpoint++]);
    }
    while (left != saveBreakpoint) storage.push_back(data[left++]);
    while (breakpoint != right) storage.push_back(data[breakpoint++]);
    for (unsigned int i = 0; i < storage.size(); ++i) data[saveLeft + i] = storage[i];
}

void sort(std::vector<unsigned int>& data)
{
    sort(data, 0, data.size());
}