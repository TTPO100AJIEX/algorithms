#include <vector>
#include "./utils/swap.cpp"

#ifdef COUNT_ELEMENTARY_OPERATIONS
    extern unsigned int elementaryOperations;
#endif

void sort(std::vector<unsigned int>& data)
{
    for (unsigned int i = 1; i < data.size(); ++i)
    {
        int left = -1, right = i;
        while (right - left > 1)
        {
            int mid = (left + right) >> 1;
            if (data[mid] > data[i]) right = mid;
            else left = mid;
        }
        for (unsigned int j = i; j > (unsigned int)(right); --j) swap(data[j], data[j - 1]);
    }
}