#include <vector>

#ifdef COUNT_ELEMENTARY_OPERATIONS
    extern unsigned int elementaryOperations;
#endif

static unsigned int CiurSequence[] = { 1750, 701, 301, 132, 57, 23, 10, 4, 1 };
void sort(std::vector<unsigned int>& data)
{
    for (const unsigned int gap : CiurSequence)
    {
        for (unsigned int i = gap; i < data.size(); ++i)
        {
            unsigned int pivot = data[i], j = i;
            for ( ; j >= gap && data[j - gap] > pivot; j -= gap) data[j] = data[j - gap];
            data[j] = pivot;
        }
    }
}