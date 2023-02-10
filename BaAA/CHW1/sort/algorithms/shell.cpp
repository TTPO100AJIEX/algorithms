#include <vector>

#ifdef COUNT_ELEMENTARY_OPERATIONS
    extern unsigned int elementaryOperations;
#endif

void sort(std::vector<unsigned int>& data)
{
    for (unsigned int gap = data.size() / 2; gap > 0; gap >>= 1)
    {
        for (unsigned int i = gap; i < data.size(); ++i)
        {
            unsigned int pivot = data[i], j = i;
            for ( ; j >= gap && data[j - gap] > pivot; j -= gap) data[j] = data[j - gap];
            data[j] = pivot;
        }
    }
}