#pragma once

#include <vector>
#include "./utils/countOps.h"

#ifdef COUNT_ELEMENTARY_OPERATIONS
    extern unsigned int elementaryOperations;
#endif

void sort(std::vector<unsigned int>& data)
{
    unsigned int max = 0;
    for (const unsigned int& item : data)
    {
        if (item > max) max = item;
    }
    std::vector<unsigned int> counter(max + 1, 0), res(data.size());
    for (std::vector<unsigned int>::iterator cur = data.begin(); cur != data.end(); ++cur) ++counter[*cur];
    for (std::vector<unsigned int>::iterator it = counter.begin() + 1; it != counter.end(); ++it) *it += *(it - 1);
    for (std::vector<unsigned int>::reverse_iterator cur = data.rbegin(); cur != data.rend(); ++cur) res[--counter[*cur]] = *cur;
    data = res;
}