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

	void operator =(T data)
	{
		this->Data = data;
	}

	~Node()
	{		
	}	
};

template<typename T>
class LinkedList
{
private:
	void Delete()	//	deletes the current linked list instance
	{
		Node<T>* current = this->Head
				,*next;

		while (current != nullptr)
		{
			next = current->Next;

			delete current;
			
			current = next;
		}	
	}

	void Delete(Node<T>* node)
	{
		if (node)
		{
			this->Delete(node->Next);
			delete node;
		}
	}

	Node<T>* Traverse()
	{	
		return this->Traverse(this->Head);
	}

	Node<T>* Traverse(Node<T>* node)
	{
		if (node->Next == nullptr)
			return node;
		
		return this->Traverse(node->Next);	
	}

	Node<T>* Traverse(Node<T>* node, int start, int end)
	{
		if (start < end)
			return this->Traverse(node->Next, ++start, end);
		
		return node;
	}
	
public:
	Node<T>* Head,	//	Head node.	
			*Tail;	//	Tail node.

	unsigned int Size { 0 };
	
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

		//for (int x = 0; x < index; x++)
		//	node = node->Next;

		node = this->Traverse(node, 0, index);

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

	void DeleteNode(unsigned int index)
	{
		Node<T>* node;

		if ((node = this->GetNode(index)) == nullptr)
			return;

		if (node->Previous != nullptr && node->Next != nullptr)
		{	
			node->Previous->Next = node->Next; 
			node->Next->Previous = node->Previous;
		}

		delete node;
	}

	void SetNodeData(T data, int index)	//	Sets the data to the node at provided index
	{
		Node<T>* node;

		if ((node = this->GetNode(index)) == nullptr)	
			return;

		node->Data = data;
	}
		
	Node<T>* operator [](unsigned int index)
	{
		return this->GetNode(index);
	}
	
	LinkedList() : Head(nullptr), Tail(nullptr)
	{
	}
	
	LinkedList(Node<T>* node) : Head(node), Tail(this->Head->Next)
	{
		this->Size++; 
	}
	
	LinkedList(const LinkedList& linkedList) : Head(linkedList.Head)
	{
		for (Node<T>* node = linkedList.Head; node->Next != nullptr; node = node->Next)
		{
			this->AddNode(node);
			
			this->Size++;
		}
	}

	~LinkedList()
	{
		this->Delete(this->Head);
	}
};

