#include <iostream>
#include <string>
#include "AVLTree.cpp"

int main(void)
{
    AVLTree tree;

    tree.insert(16);
    tree.output_full();
    std::cout << std::endl;

    tree.insert(10);
    tree.output_full();
    std::cout << std::endl;
    
    tree.insert(6);
    tree.output_full();
    std::cout << std::endl;
    
    tree.insert(12);
    tree.output_full();
    std::cout << std::endl;

    tree.insert(4);
    tree.output_full();
    std::cout << std::endl;
    
    tree.insert(18);
    tree.output_full();
    std::cout << std::endl;
    
    tree.insert(2);
    tree.output_full();
    std::cout << std::endl;
    
    tree.insert(8);
    tree.output_full();
    std::cout << std::endl;
    
    tree.insert(14);
    tree.output_full();
    std::cout << std::endl;

    tree.erase(10);
    tree.output_full();
    std::cout << std::endl;

    tree.erase(12);
    tree.output_full();
    std::cout << std::endl;

    std::cout << "||||||||||||||||||||||||||||||||||||||||||";
    tree.output();

    std::cout << tree.getSize() << " " << tree.getHeight();

    int* data = tree.traversal();
    for (int i = 0; i < tree.getSize(); i++) std::cout << data[i] << " ";
    std::cout << std::endl;

    std::cout << *(tree.lowerBound(10)) << " " << tree.find(18);
    
    return 0;
    
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