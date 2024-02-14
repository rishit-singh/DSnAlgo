#ifndef TREE_H_
#define TREE_H_

#include <memory>
#include <functional>
#include <stdexcept>
#include <iostream>

template<typename T>
using TraverseCallback = void(*)(T);

template<typename T>
using BTraverseCallback = std::function<void(T)>;

enum class NodeDirection
{
	Left,
	Right
};


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
class BNode
{
public:
	T Data;

	int Left;

	int Right;

	int Key;

	BNode(int = -1, int = -1, int = -1); 	
	BNode(T, int = -1, int = -1, int = -1); 	
};

template<typename T>
BNode<T>::BNode(int key, int left, int right)
	: Key(key), Left(left), Right(right)
{
}

template<typename T>
BNode<T>::BNode(T data, int key, int left, int right)
	: Data(data), Key(key), Left(left), Right(right)
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

template<typename T>
class BinaryTree
{
private:
	size_t Height;

	BTraverseCallback<T> OnTraverse;

	virtual void Traverse(const BNode<T>& node) const; 

public:
	std::vector<BNode<T>> Nodes;
	
	size_t GetHeight() const noexcept; 

	virtual bool IsComplete() const noexcept;	
    virtual bool IsFull() const noexcept;	
	virtual bool IsPerfect() const noexcept;	

	virtual void Insert(T, size_t, NodeDirection);
	virtual void Delete(size_t);
	
	[[nodiscard]] virtual BNode<T>& At(size_t);

	virtual void Traverse() const; 
 
	void SetOnTraverse(BTraverseCallback<T>);

	BinaryTree(std::vector<BNode<T>> = {}, const size_t = 1024);
	~BinaryTree(); 
};

template<typename T>
BinaryTree<T>::BinaryTree(std::vector<BNode<T>> initial, const size_t maxSize)
	: Nodes(maxSize), Height(0), OnTraverse([](T data){})
{
}

template<typename T>
BinaryTree<T>::~BinaryTree()
{
}

template<typename T>
BNode<T>& BinaryTree<T>::At(size_t index) 
{
	return this->Nodes[index];
}

template<typename T>
void BinaryTree<T>::Insert(T val, size_t index, NodeDirection direction)
{
	if (index > this->Nodes.size())
		throw std::out_of_range("Index out of range");

	if (this->Nodes[0].Key == -1)
	{
		this->Nodes[0] = BNode<T>(val, 0, -1, -1);

		return;
	}

	BNode<T>& node = this->Nodes[index];

	if (node.Key == -1)	
		throw std::runtime_error("Node doesnt exist"); 

	if (direction == NodeDirection::Left && node.Left == -1)
	{	
		node.Left = 2 * index + 1;

		this->Nodes[node.Left] = BNode<T>(val, node.Left, -1, -1);
	}
	else if (direction == NodeDirection::Right && node.Right == -1)
	{	
		node.Right = 2 * index + 2;
		this->Nodes[node.Right] = BNode<T>(val, node.Right, -1, -1);
	}
	else
		throw std::runtime_error("Node already has a child"); 
}

template<typename T>
void BinaryTree<T>::Traverse(const BNode<T>& node) const
{ 
	if (node.Key == -1)
		return;

	std::cout << "curr: " << node.Key 
			<< " left: " << this->Nodes[node.Left].Key
			<< " right: " << this->Nodes[node.Right].Key << '\n';
	

	if (node.Left != -1)
		this->Traverse(this->Nodes[node.Left]);

	this->OnTraverse(node.Data);

	if (node.Right != -1)
		this->Traverse(this->Nodes[node.Right]);
}

template<typename T>
void BinaryTree<T>::Traverse() const
{
	this->Traverse(this->Nodes[0]);	
}

template<typename T>
void BinaryTree<T>::Delete(size_t index)
{
}

template<typename T>
void BinaryTree<T>::SetOnTraverse(BTraverseCallback<T> callback)
{
	this->OnTraverse = callback;
}

template<typename T>
bool BinaryTree<T>::IsComplete() const noexcept
{
	return false;
}

template<typename T>
bool BinaryTree<T>::IsFull() const noexcept
{
	return false;
}

template<typename T>
bool BinaryTree<T>::IsPerfect() const noexcept
{
	return false;
}

#endif
  
