#pragma once

#ifdef COUNT_ELEMENTARY_OPERATIONS
    extern unsigned long long int elementaryOperations;
    #define countOps(amount) elementaryOperations += amount;
#else
    #define countOps(amount) 
#endif