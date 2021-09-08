#include <stdlib.h>

template <typename T>
struct Node
{
	T Data;

	Node<T>* Head,
		*Next,
		*Previous;

	Node()
	{
	}

	Node(T data) : Data(data), Head(nullptr), Next(nullptr), Previous(nullptr)
	{
	}
	
	Node(T data, Node<T>* head) : Data(data), Head(head), Next(nullptr), Previous(nullptr)
	{
	}

	Node(T data, Node<T>* head, Node<T>* next) : Data(data), Head(head), Next(next), Previous(nullptr)
	{
	}

	Node(T data, Node<T>* head, Node<T>* next, Node<T>* previous) : Data(data), Head(head), Next(next), Previous(previous)
	{
	}

	~Node()
	{
		if (this->Previous != nullptr && this->Next != nullptr)
		{	
			this->Previous->Next = this->Next; 
			this->Next->Previous = this->Previous;
		}
	}	
};

template<typename T>
class LinkedList
{
private:
	void Delete()	//	deletes the current linked list instance recursively
	{
				
	}

	Node<T>* Traverse()
	{	
		Node<T>* node;

		for (node = this->Head; node->Next != nullptr; node = node->Next);
		
		return node;
	}

public:
	Node<T>* Head,	//	Head node.	
			*Tail;	//	Tail node.

	Node<T>* GetFrontNode()	//	Returns the first/head node of the list.
	{
		return this->Head;
	}
		
	Node<T>* GetBackNode()	//	Returns the last node in the list.
	{
		return this->Traverse();
	}	

	Node<T>* GetMidNode()
	{
		return this->GetNode((this->Size - 1) / 2);
	}

	Node<T>* GetNode(int index)	//	Returns the node at the provided index in list.
	{
		if (index > (this->Size - 1) || index <  0)	//	Range check. 
			return nullptr;
		
		Node<T>* node = this->Head;

		for (int x = 0; x < index; x++)
			node = node->Next;

		return node;
	}
   	
	Node<T>* AddNode(T data)	//	Adds a new node with the provided data to the current linked list instance.
	{
		Node<T>* node = this->Traverse();

		node->Next = new Node<T>(data, this->Head, nullptr, node);	

		this->Tail = node->Next;

		this->Size++;
			
		return node->Next;	
	}

	Node<T>* AddNode(Node<T>* node)	//	Adds the provided node to the current linked list instance.
	{
		Node<T>* temp; 	//	temp node
		
		if (node == nullptr)	//	null check
			return node; 
	
		(temp = this->Traverse())->Next = node;

		node->Previous = temp;
	
		this->Size++;
		
		return node;		
	}
	
	void SetNodeData(T, int);	//	Sets the data to the node at provided index
		
	unsigned int Size;

	LinkedList() : Head(nullptr), Tail(nullptr), Size(0)
	{
	}
	
	LinkedList(Node<T>* node) : Head(node), Tail(this->Head->Next)
	{
		this->Size++; 
	}
	
	LinkedList(const LinkedList& linkedList) : Head(linkedList.Head), Size(0)
	{
		for (Node<T>* node = linkedList.Head; node->Next != nullptr; node = node->Next)
		{
			this->AddNode(node);
			
			this->Size++;
		}
	}

	~LinkedList()
	{

		for (Node<T>* node = this->Head->Next; node->Next != nullptr; node = node->Next)
			delete node;

		delete this->Head;
	}
};

