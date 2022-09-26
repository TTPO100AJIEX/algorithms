#include "List.cpp"

int main(void)
{
    List list;
    //list.pushBack(1);
    //list.pushFront(2);
    //list.pushBack(3);
    //list.pushFront(4);
    //list.pushBack(5);
    //std::cout << list.pop(20) << std::endl;
    list.pushBack(1);
    list.pushBack(2);
    list.pushBack(3);
    list.pushBack(4);
    list.pushBack(5);
    list.pushBack(6);
    list.pushBack(7);
    list.pushBack(8);
    list.pushBack(9);
    std::cout << list.pop(0) << std::endl;
    list.output();
    return 0;
}