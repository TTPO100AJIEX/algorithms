#include <vector>

#ifdef COUNT_ELEMENTARY_OPERATIONS
    extern unsigned int elementaryOperations;
#endif

#include <algorithm>
void sort(std::vector<unsigned int>& data)
{
    std::sort(data.begin(), data.end());
}