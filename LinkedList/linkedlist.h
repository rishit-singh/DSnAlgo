#ifndef LINKEDLIST_H

#define LINKEDLIST_H

#include <stdlib.h>

template<typename T>
struct Node	//	Stores the node.
{
	T Value;
	
	Node<T>* Next;
		
	Node() : Value(NULL), Next(nullptr)
	{
	}
	
	Node(T value) : Value(value), Next(nullptr)
	{
	}
	
	Node(T value, Node<T>* next) : Value(value), Next(next)
	{
	}
};

template<typename T>
class LinkedList
{
public:
	Node<T>* Head;	//	Head node
		
	unsigned int Count;	//	element count

	Node<T>* Traverse()
	{
		Node<T>* nodeTemp = nullptr;

		for (nodeTemp = this->Head; nodeTemp->Next != nullptr; nodeTemp = nodeTemp->Next);

		return nodeTemp;
	}

	Node<T>* AddNode(Node<T>* node)
	{
		this->Traverse()->Next = node;
		
		this->Count++;
	}
	
	void RemoveNode(int index)
	{
		Node<T>* nodeTemp = this->GetNode(index)->Next;

		delete this->GetNode(index);

		this->GetNode(index - 1)->Next = nodeTemp;
	}
	
	Node<T>* GetNode(int index)
	{
		if (index > this->Count || index < 0)
			return nullptr;  
			
		Node<T>* nodeTemp = this->Head;

		for (int x = 0; x < index; x++)
			nodeTemp = nodeTemp->Next;

		return nodeTemp;
	}

	T GetValue(int index)
	{
		Node<T>* nodeTemp;

		return ((nodeTemp = this->GetNode(index)) == nullptr) ? NULL : nodeTemp->Value;
	}

	Node<T>* UpdateNode(T value, int index)
	{		
		Node<T>* nodeTemp = this->GetNode(index);

		nodeTemp->Value = value;

		return nodeTemp;
	}

	T operator [](int index)
	{
		return this->GetValue(index);
	}
	
	LinkedList() : Head(nullptr), Count(NULL)
	{
	}
	
	LinkedList(T value) : Head(new Node<T>(value)), Count(NULL)
	{
	}
		
	LinkedList(Node<T>* node) : Head(node), Count(1)
	{
	}	

	~LinkedList()
	{
		delete this->Head;
	}
};

#endif

