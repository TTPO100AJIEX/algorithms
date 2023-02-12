#pragma once

#include "./countOps.h"

template <typename T>
void swap(T& a, T& b)
{
    countOps(2); // access a, create and initialize c
    T c = std::move(a);
    countOps(2); // access b, assign to a
    a = std::move(b);
    countOps(2); // access c, assign to b
    b = std::move(c);
}