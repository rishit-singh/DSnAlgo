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

	Node(std::shared_ptr<Node<T>>, std::shared_ptr<Node<T>>);
};

template<typename T>
Node<T>::Node(std::shared_ptr<Node<T>> left, std::shared_ptr<Node<T>> right) 
	: Left(left), Right(right)
{
}

template<typename T>
class Tree
{
public:
	virtual void Traverse(TraverseCallback<T>) = 0;
	virtual void Insert(T) = 0;
	virtual Node<T> Get(T); 
};

#endif
 

