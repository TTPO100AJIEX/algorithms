#pragma once

#ifdef COUNT_ELEMENTARY_OPERATIONS
    unsigned int elementaryOperations = 0;
    #define countOps(amount) elementaryOperations += amount;
#else
    #define countOps(amount) 
#endif