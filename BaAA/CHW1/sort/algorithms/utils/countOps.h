#pragma once

// Create the macro to count the operations
#ifdef COUNT_ELEMENTARY_OPERATIONS
    extern unsigned long long int elementaryOperations;
    #define countOps(amount) elementaryOperations += amount;
#else
    #define countOps(amount) 
#endif