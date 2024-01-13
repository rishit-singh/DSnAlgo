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
	tree.Insert(11); 
	tree.Insert(0); 
	tree.Insert(2); 

	tree.Delete(0);

	tree.Traverse([](int value, Direction direction){ std::cout << value << " " << direction << "\n";});	

		
	std::cout << std::get<1>(tree.Get(2)) << '\n';

	return 0;
}
