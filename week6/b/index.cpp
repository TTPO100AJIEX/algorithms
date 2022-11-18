#include <iostream>
#include "AVLTree.cpp"

int main(void)
{
    AVLTree tree;

    tree.insert(1);
    tree.insert(3);
    tree.insert(2);

    int* data = tree.traversal();
    for (int i = 0; i < tree.getSize(); i++) std::cout << data[i] << " ";
    std::cout << std::endl;
    
    tree.erase(1);
    data = tree.traversal();
    for (int i = 0; i < tree.getSize(); i++) std::cout << data[i] << " ";
    std::cout << std::endl;

    tree.erase(3);
    tree.erase(2);
    
    //tree.output();
}