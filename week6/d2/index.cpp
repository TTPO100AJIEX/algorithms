#include <iostream>
#include "RBTree.cpp"

int main(void)
{
    RBTree<int> rb_tree({ 1, 2, 3 });
    rb_tree.insert(1);
    rb_tree.insert(5);
    rb_tree.insert(4);
    rb_tree.erase(5);

    std::cout << std::endl;

    RBTree<int> rb_tree2 = rb_tree;
    return 0;
}