#include "linkedlist.h"
#include <iostream>

template<typename T>
static void PrintList(LinkedList<T>& linkedList)
{
	Node<T>* node;
	
	for (int x = 0; x < (linkedList.Size - 1); x++)
		std::cout << x << ": " << (node = linkedList.GetNode(x))->Data << ";\n";
}

int main()
{
	LinkedList<int> linkedList = LinkedList<int>(new Node<int>(10)), linkedList1;

	for (int x = 20; x <= 100; x += 10)	
		linkedList.AddNode(new Node<int>(x));

	//linkedList1 = LinkedList<int>(linkedList);

	//	PrintList(linkedList);

	return 0;
}
