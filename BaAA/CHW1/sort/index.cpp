#include <iostream>
#include <fstream>
#include <vector>
#ifdef COUNT_TIME
    #include <chrono>
#endif

#if defined(BINARY_INSERTION)
    #include "./algorithms/binary-insertion.h"
#elif defined(BUBBLE_1)
    #include "./algorithms/bubble-1.h"
#elif defined(BUBBLE_2)
    #include "./algorithms/bubble-2.h"
#elif defined(BUBBLE)
    #include "./algorithms/bubble.h"
#elif defined(COUNTING)
    #include "./algorithms/counting.h"
#elif defined(HEAP)
    #include "./algorithms/heap.h"
#elif defined(INSERTION)
    #include "./algorithms/insertion.h"
#elif defined(MERGE)
    #include "./algorithms/merge.h"
#elif defined(QUICK)
    #include "./algorithms/quick.h"
#elif defined(RADIX)
    #include "./algorithms/radix.h"
#elif defined(SELECTION)
    #include "./algorithms/selection.h"
#elif defined(SHELL_CIUR)
    #include "./algorithms/shell-ciur.h"
#elif defined(SHELL)
    #include "./algorithms/shell.h"
#else
    #error "One of sorting algorithms must be defined"
#endif

#ifdef COUNT_ELEMENTARY_OPERATIONS
    unsigned long long int elementaryOperations = 0;
    #include "./algorithms/utils/countOps.h"
#endif

int main(int argc, char** argv)
{
    std::ifstream fin(argv[1]);
    unsigned int size; fin >> size;
    std::vector <unsigned int> data(size);
    for (unsigned int i = 0; i < size; i++) fin >> data[i];

	#ifdef COUNT_TIME
        using clock = std::conditional_t<std::chrono::high_resolution_clock::is_steady, std::chrono::high_resolution_clock, std::chrono::steady_clock>;
        clock::time_point start = clock::now();
    #endif
    sort(data);
	#ifdef COUNT_TIME
        clock::time_point end = clock::now();
    #endif

    #if defined(DEBUG) || defined(TEST)
        for (unsigned int i = 0; i < size; i++)
        {
            std::cout << data[i];
            if (i != size - 1) std::cout << " ";
        }
    #endif

	#ifdef COUNT_TIME
        std::cout << "\nTime spent: " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() << "ns";
    #endif
    #ifdef COUNT_ELEMENTARY_OPERATIONS
        std::cout << "\nOperations done: " << elementaryOperations;
    #endif
    
    return 0;
}