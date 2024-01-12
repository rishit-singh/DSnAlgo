#include "BST.hpp"
#include <iostream>

template<typename T>
constexpr void AssertEqual(T a, T b)
{
	if (a != b)
		throw "Test failed";
}

int main(int argc, char** argv) 
{
	BinarySearchTree<int> tree = BinarySearchTree<int>();
	
	tree.Insert(10); 
	tree.Insert(0); 
	tree.Insert(2); 

	tree.Traverse([](int value, Direction direction){ std::cout << value << "\n";  });	

	std::cout << **tree.Get(2).first << '\n';

	return 0;
}
