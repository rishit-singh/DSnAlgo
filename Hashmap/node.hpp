#ifndef NODE_H
#define NODE_H

template<typename T>
class Node
{
	T Data;

	Node<T>* Next;

	Node(T data, Node<T>* next) : Data(data), Next(next)
	{
	}
};

#endif
