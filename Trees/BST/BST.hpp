#ifndef BST_H_
#define BST_H_

#include "tree.hpp"

enum class Direction
{
	Left,
	Right
};

template<typename T>
using BSTTraverseCallback = void(*)(T, Direction);

template<typename T>
class BinarySearchTree : public Tree<T>
{
protected:
	std::shared_ptr<Node<T>> SeekNode(T, std::shared_ptr<Node<T>>);

	void Insert(T, std::shared_ptr<Node<T>>);

public:
	std::shared_ptr<Node<T>> Root;	

	void Insert(T) override;
	
	void Traverse(TraverseCallback<T>) override;
	void Traverse(std::shared_ptr<Node<T>>, TraverseCallback<T>) override;

	void Traverse(BSTTraverseCallback<T>);
	void Traverse(std::shared_ptr<Node<T>>, BSTTraverseCallback<T>);

	std::shared_ptr<Node<T>> Get(T) override;

	BinarySearchTree(std::shared_ptr<Node<T>> = nullptr);
	virtual ~BinarySearchTree() = default;
};


template<typename T>
BinarySearchTree<T>::BinarySearchTree(std::shared_ptr<Node<T>> root) : Root(root)
{}

template<typename T>
void BinarySearchTree<T>::Traverse(std::shared_ptr<Node<T>> node, TraverseCallback<T> callback) 
{
}

template<typename T>
void BinarySearchTree<T>::Traverse(BSTTraverseCallback<T> callback) 
{
	this->Traverse(this->Root, callback);
}

template<typename T>
void BinarySearchTree<T>::Traverse(std::shared_ptr<Node<T>> node, BSTTraverseCallback<T> callback) 
{
	if (!node)
		return;

	this->Traverse(node->Left, callback);
		
	callback(node->Data, Direction::Left); 

	this->Traverse(node->Right, callback);
}

template<typename T>
void BinarySearchTree<T>::Traverse(TraverseCallback<T> callback) 
{
}

template<typename T>
std::shared_ptr<Node<T>> BinarySearchTree<T>::Get(T value)
{
	return this->SeekNode(value, this->Root);
} 

template<typename T>
std::shared_ptr<Node<T>> BinarySearchTree<T>::SeekNode(T value, std::shared_ptr<Node<T>> node) 
{
	if (!node)
		return nullptr;

	if (node->Data == value)
		return node;
	
	if (node->Data < value && node->Right)
		return this->SeekNode(value, node->Right);

	if (node->Data > value && node->Left)
		return this->SeekNode(value, node->Left);

	return nullptr;
}

template<typename T>
void BinarySearchTree<T>::Insert(T value, std::shared_ptr<Node<T>> node)
{
	Direction direction = Direction::Left; 

	if (value > node->Data)
		direction = Direction::Right;
	else if (value < node->Data)
		direction = Direction::Left;
	
	if (direction == Direction::Left)
	{
		if (!node->Left)
			node->Left = std::make_shared<Node<T>>(value, nullptr, nullptr);
		else
			this->Insert(value, node->Left); 
	}
	else if (direction == Direction::Right)
	{
		if (!node->Right)
			node->Right = std::make_shared<Node<T>>(value, nullptr, nullptr);
		else
			this->Insert(value, node->Right); 
	}
}

template<typename T>
void BinarySearchTree<T>::Insert(T value) 
{	
	if (!this->Root) 
		this->Root = std::make_shared<Node<T>>(value, nullptr, nullptr);
	
	this->Insert(value, this->Root);
}


#endif



