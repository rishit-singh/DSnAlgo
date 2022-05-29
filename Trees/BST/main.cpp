#include "tree.h"
#include <stdlib.h>

int main(int argc, char **argv)
{
    int num = atoi(argv[1]);

    // std::cout << "\n" << num << '\n';

    BinarySearchTree<int> binarySearchTree = BinarySearchTree<int>(new Node<int>(0));


    int n[8] = { 83, 77, 15, 93, 35, 86, 92, 49 };

    for (int x = 0; x < 8; x++)
        binarySearchTree.Insert(n[x]);

    std::cout << '\n';

    binarySearchTree.Traverse();

    std::cout << "\nExists: " << binarySearchTree.Search(num) << '\n';

    BinarySearchTree<int>::NodePairInfo node = binarySearchTree.GetNode(num);

    binarySearchTree.Delete(num);

    std::cout << '\n';

    binarySearchTree.Traverse();
    // binarySearchTree.num);
    // binarySearchTree.Traverse();
    std::cout << '\n';

    return 0;
}
