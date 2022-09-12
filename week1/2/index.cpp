#include <iostream>
#include "deque.cpp";

int main(void)
{
    Deque deque;
    deque.pushBack(1);
    deque.pushBack(2);
    deque.pushMiddle(3);
    std::cout << deque.popFront() << std::endl;
    deque.pushBack(4);
    deque.pushMiddle(5);
    std::cout << deque.popFront() << std::endl;
    std::cout << deque.popFront() << std::endl;
    std::cout << deque.popFront() << std::endl;
    std::cout << deque.popFront() << std::endl;
    return 0;
}