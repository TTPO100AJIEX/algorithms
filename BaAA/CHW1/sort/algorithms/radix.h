#pragma once

#include <vector>
#include "./utils/countOps.h"
#include "./utils/swap.h"

#ifdef COUNT_ELEMENTARY_OPERATIONS
    extern unsigned int elementaryOperations;
#endif

void sort(std::vector<unsigned int>& data)
{
    std::vector<unsigned int> res(data.size());
    for (unsigned int offset = 0; offset < 16; offset += 8)
    {
        unsigned int counter[256] = { 0 };
        for (unsigned int i = 0; i < data.size(); ++i) ++counter[(data[i] >> offset) & 255];
        for (unsigned int i = 1; i < 256; ++i) counter[i] += counter[i - 1];
        for (int i = data.size() - 1; i >= 0; --i) res[--counter[(data[i] >> offset) & 255]] = data[i];
        swap(data, res);
    }
}