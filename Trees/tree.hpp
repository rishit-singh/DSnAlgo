#ifndef TREE_H_
#define TREE_H_

#include <memory>

template<typename T>
using TraverseCallback = void(*)(T);

template<typename T>
class Node
{
public:
	T Data;

	std::shared_ptr<Node<T>> Left;
	
	std::shared_ptr<Node<T>> Right;

	Node(T, std::shared_ptr<Node<T>>, std::shared_ptr<Node<T>>);
};

template<typename T>
Node<T>::Node(T data, std::shared_ptr<Node<T>> left, std::shared_ptr<Node<T>> right) 
	: Data(data), Left(left), Right(right)
{
}

template<typename T>
class Tree
{
public:
	std::shared_ptr<Node<T>> Root; 
		
	virtual void Traverse(std::shared_ptr<Node<T>>, TraverseCallback<T>) = 0;
	virtual void Traverse(TraverseCallback<T>) = 0;
	virtual void Insert(T) = 0;
	virtual std::shared_ptr<Node<T>> Get(T) = 0; 
};

#endif
 

