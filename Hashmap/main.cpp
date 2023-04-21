#include <iostream>
#include "hashmap.hpp"


void PrintList(LinkedList<int>& list)
{
	for (KeyPairNode<int>* node = list.Head; node; node = node->Next)
		std::cout << node->Data << '\n';	
}

int main(int argc, char** argv)
{
	LinkedList<int> list = LinkedList<int>("random", 0); 

	for (int x = 1; x < 10; x++);


	return 0;
}


