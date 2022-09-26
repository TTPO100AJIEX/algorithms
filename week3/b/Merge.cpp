#include <list>

#include <iostream>

using std::list;
 
list<int> merge(list<int> first, list<int>& second)
{
    first.merge(second);
    return first;
}