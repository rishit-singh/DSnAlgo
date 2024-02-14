#include "tree.hpp"

#include <iostream>

int main(int argc, char** argv)
{
    BinaryTree<int> tree;

    tree.SetOnTraverse([](int val){ std::cout << val << '\n'; });

    tree.Insert(0, 0, NodeDirection::Left);
    tree.Insert(1, 0, NodeDirection::Left);
    tree.Insert(2, 0, NodeDirection::Right);
    tree.Insert(3, tree.At(0).Right, NodeDirection::Left);


    tree.Traverse();

    return 0;
}