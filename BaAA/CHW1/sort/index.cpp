#include <iostream>
#include <fstream>
#include <vector>

#if defined(BINARY_INSERTION)
    #include "./algorithms/binary-insertion.cpp"
#elif defined(BUBBLE_1)
    #include "./algorithms/bubble-1.cpp"
#elif defined(BUBBLE_2)
    #include "./algorithms/bubble-2.cpp"
#elif defined(BUBBLE)
    #include "./algorithms/bubble.cpp"
#elif defined(COUNTING)
    #include "./algorithms/counting.cpp"
#elif defined(HEAP)
    #include "./algorithms/heap.cpp"
#elif defined(INSERTION)
    #include "./algorithms/insertion.cpp"
#elif defined(MERGE)
    #include "./algorithms/merge.cpp"
#elif defined(QUICK)
    #include "./algorithms/quick.cpp"
#elif defined(RADIX)
    #include "./algorithms/radix.cpp"
#elif defined(SELECTION)
    #include "./algorithms/selection.cpp"
#elif defined(SHELL_CIUR)
    #include "./algorithms/shell-ciur.cpp"
#elif defined(SHELL)
    #include "./algorithms/shell.cpp"
#else
    #error "One of sorting algorithms must be defined"
#endif

#ifdef COUNT_ELEMENTARY_OPERATIONS
    unsigned int elementaryOperations = 0;
#endif
#ifdef COUNT_TIME
    #include <chrono>
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