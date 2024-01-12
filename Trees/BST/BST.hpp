#ifndef BST_H_
#define BST_H_

#include "tree.hpp"
#include <functional>

template<typename T>
using BSTTraverseCallback = std::function<void(T, Direction)>;

template<typename T>
class BinarySearchTree : public Tree<T>
{
protected:
	std::pair<std::shared_ptr<Node<T>>, Direction> SeekNode(T, std::shared_ptr<Node<T>>, Direction = Direction::Left);

	void Insert(T, std::shared_ptr<Node<T>>);

public:
	std::shared_ptr<Node<T>> Root;	

	void Insert(T) override;

	T Delete(T);

	void Traverse(TraverseCallback<T>) override;
	void Traverse(std::shared_ptr<Node<T>>, TraverseCallback<T>) override;

	void Traverse(BSTTraverseCallback<T>);
	void Traverse(std::shared_ptr<Node<T>>, BSTTraverseCallback<T>);

	[[nodiscard]] std::pair<std::shared_ptr<Node<T>>, Direction> Get(T) override;

	BinarySearchTree(std::shared_ptr<Node<T>> = nullptr);

	virtual ~BinarySearchTree() = default;
};


template<typename T>
BinarySearchTree<T>::BinarySearchTree(std::shared_ptr<Node<T>> root) : Root(root)
{}

template<typename T>
void BinarySearchTree<T>::Traverse(TraverseCallback<T> callback) 
{
	this->Traverse(this->Root, callback);
}

template<typename T>
void BinarySearchTree<T>::Traverse(std::shared_ptr<Node<T>> node, TraverseCallback<T> callback) 
{
	if (!node)
		return;

	this->Traverse(node->Left, callback);
		
	callback(node->Data); 

	this->Traverse(node->Right, callback);
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
std::pair<std::shared_ptr<Node<T>>, Direction> BinarySearchTree<T>::Get(T value)
{
	return this->SeekNode(value, this->Root);
} 

template<typename T>
std::pair<std::shared_ptr<Node<T>>, Direction> BinarySearchTree<T>::SeekNode(T value, std::shared_ptr<Node<T>> node, Direction direction) 
{
	if (!node)
		return std::make_pair(nullptr, Direction::Left);

	if (node->Data == value)
		return std::make_pair(node, direction);
	
	if (node->Data < value && node->Right)
		return this->SeekNode(value, node->Right, Direction::Right);

	else if (node->Data > value && node->Left)
		return this->SeekNode(value, node->Left, Direction::Left);

	return std::make_pair(nullptr, Direction::Left);
}

template<typename T>
void BinarySearchTree<T>::Insert(T value, std::shared_ptr<Node<T>> node)
{
	Direction direction = Direction::Left; 

	if (value > node->Data)
		direction = Direction::Right;

	else if (value < node->Data)
		direction = Direction::Left;
	
	if (direction == Direction::Left && !node->Left)
		node->Left = std::make_shared<Node<T>>(value, nullptr, nullptr);

	else if (direction == Direction::Left && node->Left)
		this->Insert(value, node->Left); 

	else if (direction == Direction::Right && !node->Right)
			node->Right = std::make_shared<Node<T>>(value, nullptr, nullptr);

	else if (direction == Direction::Right && node->Right)
		this->Insert(value, node->Right); 
}

template<typename T>
void BinarySearchTree<T>::Insert(T value) 
{	
	if (!this->Root) 
		this->Root = std::make_shared<Node<T>>(value, nullptr, nullptr);
	
	this->Insert(value, this->Root);
}

template<typename T>
T BinarySearchTree<T>::Delete(T value)
{
	auto node = this->Get(value);

	if (!node)
		throw std::runtime_error("Value to be deleted doesn't exist");
	
}


#endif



