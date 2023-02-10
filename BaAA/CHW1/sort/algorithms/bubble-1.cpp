#include <vector>
#include "./utils/swap.cpp"

#ifdef COUNT_ELEMENTARY_OPERATIONS
    extern unsigned int elementaryOperations;
#endif

void sort(std::vector<unsigned int>& data)
{
    for (unsigned int i = 0; i < data.size() - 1; ++i)
    {
        bool doContinue = false;
        for (unsigned int j = 0; j < data.size() - i - 1; ++j)
        {
            if (data[j] > data[j + 1]) { swap(data[j], data[j + 1]); doContinue = true; }
        }
        if (!doContinue) break;
    }
}