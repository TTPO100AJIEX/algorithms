#include <iostream>
#include <string>
#include "AVLTree.cpp"

int main(void)
{
    AVLTree tree;

    tree.insert(2);
    tree.insert(3);
    tree.insert(1);

    tree.output();


    return 0;

    tree.insert(16);
    tree.output();
    std::cout << std::endl;

    tree.insert(10);
    tree.output();
    std::cout << std::endl;
    
    tree.insert(6);
    tree.output();
    std::cout << std::endl;
    
    tree.insert(12);
    tree.output();
    std::cout << std::endl;

    tree.insert(4);
    tree.output();
    std::cout << std::endl;
    
    tree.insert(18);
    tree.output();
    std::cout << std::endl;
    
    tree.insert(2);
    tree.output();
    std::cout << std::endl;
    
    tree.insert(8);
    tree.output();
    std::cout << std::endl;
    
    tree.insert(11);
    tree.output();
    std::cout << std::endl;
    
    std::cout << tree.find(10);

    return 0;

    tree.erase(10);
    tree.output();
    std::cout << std::endl;
    
    //tree.erase(3);
    /*
    int* data = tree.traversal();
    for (int i = 0; i < tree.getSize(); i++) std::cout << data[i] << " ";
    std::cout << std::endl;
    
    data = tree.traversal();
    for (int i = 0; i < tree.getSize(); i++) std::cout << data[i] << " ";
    std::cout << std::endl;

    tree.erase(1);
    data = tree.traversal();
    for (int i = 0; i < tree.getSize(); i++) std::cout << data[i] << " ";
    std::cout << std::endl;

    tree.erase(2);
    data = tree.traversal();
    for (int i = 0; i < tree.getSize(); i++) std::cout << data[i] << " ";
    std::cout << std::endl;*/

    
    //tree.output();
}