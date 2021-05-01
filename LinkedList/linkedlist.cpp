#include <iostream>
#include <stdlib.h>
#include "linkedlist.h"

int main(int argc, char** argv)
{
	int value = atoi(argv[1]), index = atoi(argv[2]);
	
	LinkedList<int> linkedList = LinkedList<int>(0);
	
	for (int x = 1; x < 10; x++)
		linkedList.AddNode(new Node<int>(x));

	linkedList.UpdateNode(value, index);

	std::cout << "Value: " << linkedList[index] << '\n'
			<< "TraversedValue: " << linkedList.Traverse()->Value;	
	
	return 0;
}

