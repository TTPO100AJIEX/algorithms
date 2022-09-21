#include "Vector.cpp"
#include <iostream>

int main(void)
{
    int* tmp = (int*)(calloc(5, sizeof(int)));
    for (int j = 0; j < 5; j++) tmp[j] = j;
    
    Vector test = { 1, 2, 3, 4, 5, 6, 7 };
    std::cout << test.getSize() << " " <<  test.getCapacity() << std::endl;
    for (unsigned int i = 0; i < 15; i++) test.pushBack(i);
    std::cout << test.getSize() << " " <<  test.getCapacity() << std::endl;
    for (unsigned int i = 0; i < test.getSize(); i++)
    {
        std::cout << test[i] << " ";
    }
    std::cout << std::endl;

    Vector::Iterator it = test.begin();
    std::cout << *it << " " << *(it++) << " " << *it << std::endl;
    
    Vector test3({ 1, 7, 3, 2, 9, 0, 15, -11, 7 });
    for (unsigned int i = 0; i < test3.getSize(); i++)
    {
        std::cout << test3[i] << " ";
    }
    std::cout << std::endl;
    insertionSort(test3.begin(), test3.end());
    for (unsigned int i = 0; i < test3.getSize(); i++)
    {
        std::cout << test3[i] << " ";
    }
}