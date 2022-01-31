#include "tree.h"
#include <stdlib.h>

int main(int argc, char **argv)
{
    int num = atoi(argv[1]);

    // std::cout << "\n" << num << '\n';

    BinarySearchTree<int> binarySearchTree = BinarySearchTree<int>(new Node<int>(0));

    for (int x = 1; x < 10; x++)
        binarySearchTree.Insert(x);

    binarySearchTree.Traverse();

    // std::cout << "\nExists: " << binarySearchTree.Search(num) << '\n';

    BinarySearchTree<int>::NodePairInfo node = binarySearchTree.GetNode(num);

    std::cout << "\nFound node: " << node.Previous->Data
        << "\nPrevious: " <<  node.Next->Data << '\n';

    //binarySearchTree.Delete(num);

    std::cout << '\n';

    binarySearchTree.Traverse();
    // binarySearchTree.num);
    // binarySearchTree.Traverse();

    return 0;
}
