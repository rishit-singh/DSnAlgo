#include "BST.hpp"
#include <iostream>

int main(int argc, char** argv) 
{
	BinarySearchTree<int> tree = BinarySearchTree<int>();
	
	tree.Insert(10); 
	tree.Insert(0); 
	tree.Insert(2); 

	tree.Traverse([](int value, Direction direction){ std::cout << value << "\n";  });

	
	return 0;
}
