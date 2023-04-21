#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <string_view>

template<typename T>
class KeyPairNode
{
public:
	std::string_view Key;
	
	T Data;

	KeyPairNode<T>* Next;

	KeyPairNode(std::string_view key, T data, KeyPairNode<T>* next) : Key(key), Data(data), Next(next)
	{
	}
};


template<typename T>
class LinkedList
{
protected:
	void Delete()
	{
		for (KeyPairNode<T>* node = this->Head->Next; node; node = node->Next)
				delete node;
	}

public:
	KeyPairNode<T>* Head;
	
	KeyPairNode<T>* Tail;
		
	
	void Push(KeyPairNode<T>* node)
	{
		this->Tail->Next = node;
		this->Tail = this->Tail->Next;
	}

	void Push(std::string_view key, T data)
	{
		this->Push(new KeyPairNode<T>(key, data, nullptr));
	}
	
	LinkedList(KeyPairNode<T>* node) : Head(node), Tail(Head)
	{
	}	

	LinkedList(std::string_view key, T data) : Head(new KeyPairNode<T>(key, data, nullptr)), Tail(Head)
	{
	}
};	

#endif
