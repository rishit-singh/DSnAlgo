// Tree implementations.

#ifndef TREE_H
#define TREE_H

#include "node.h"
#include <cinttypes>
#include <iostream>
#include <utility>


// Stores the binary tree nodes and related functions.
template<typename T>
class BinarySearchTree
{
private:
        // void TraversePreOrder()
        // {
        // }

        Node<T>* TraverseInOrder(Node<T>* node)
        {
            if (node == nullptr)
                return node;

            TraverseInOrder(node->Left);

            std::cout << " " << node->Data << " ";

            TraverseInOrder(node->Right);

            return node;
        }

        // void TraversePostOrder(T* array, size_t size)
        // {
        // }

        // void Traverse(T* array, size_t size, TraversalType traversalType) // Wrapper function for the previously defined
        // {
        //     switch (traversalType)
        //     {
        //         case TraversalType::PreOrder:
        //             this->TraversePreOrder(array, size);

        //             break;

        //         case TraversalType::InOrder:
        //             this->TraverseInOrder(array, size);


        //             break;

        //         case TraversalType::PostOrder:
        //             this->TraversePostOrder(array, size);

        //             break;
        //     }
        // }

        void Delete(Node<T>* node) // Deletes all the nodes from the current instance of the tree.
        {
            if (!node)
                return;

            Delete(node->Left);
            Delete(node->Right);

            delete node;
        }

public:
        enum class TraversalType
        {
            PreOrder,
            PostOrder,
            InOrder
        };
       
        enum class NodeDirection
        {
            Left,
            Right
        };

        struct NodePairInfo
        {
            Node<T>* Previous,
                    *Next;

            BinarySearchTree::NodeDirection Direction;

            NodePairInfo(Node<T>* prev, Node<T>* next, BinarySearchTree::NodeDirection nodeDirection) : Previous(prev), Next(next), Direction(nodeDirection)
            {
            }
        };

        std::pair<Node<T>*, Node<T>*> GetSmallest(Node<T>* node)
        {
            if (!node)
                return std::pair<Node<T>*, Node<T>*>(nullptr, nullptr);

            Node<T>* parent = node;

            while (node->Left)
            {
                parent = node;

                node = node->Left;
            }

            std::make_pair(parent, node);
        }

        // Replaces the Next node of the provided NodePairInfo with the substituteNode
        void Transplant(NodePairInfo& nodePair, Node<T>* substituteNode)
        {
            switch (nodePair.Direction)
            {
                case NodeDirection::Left:
                    substituteNode->Left = nodePair.Next->Left;
                    substituteNode->Right = nodePair.Next->Right;

                    nodePair.Previous->Left = substituteNode;

                    break;

                case NodeDirection::Right:
                    substituteNode->Left = nodePair.Next->Left;
                    substituteNode->Right = nodePair.Next->Right;

                    nodePair.Previous->Right = substituteNode;

                    break;
            }
        }

public:
        Node<T>* Root; // Root node.

        Node<T>* Insert(T value)
        {
            Node<T>* node = new Node<T>(value),
                *temp = this->Root,
                *finalNode;

            uint8_t child = 0;

            if (this->Root == nullptr)
                this->Root = node;

            while (temp)
            {
                finalNode = temp;

                if (value < temp->Data)
                {
                    temp = temp->Left;

                    child = 0;
                }
                else
                {
                    temp = temp->Right;

                    child = 1;
                }
            }

            switch (child)
            {
                case 0:
                   finalNode->Left = node;

                    break;

                case 1:
                    finalNode->Right = node;

                    break;
            }

            return node;
        }

        bool Search(T value)
        {
            Node<T>* current = this->Root,
                *finalNode;

            while (current)
            {
                if (current->Data == value)
                    return true;

                if (value < current->Data)
                    current = current->Left;

                if (value > current->Data)
                    current = current->Right;
            }

            return false;
        }

        NodePairInfo GetNode(T value)
        {
            if (!this->Root) // Null check
                return NodePairInfo(nullptr, nullptr, NodeDirection::Left);

            NodePairInfo node = NodePairInfo(nullptr, this->Root, NodeDirection::Left);

            if (value == this->Root->Data)
                return node;

            while (node.Next) // Runs until next node isnt null.
            {
                if (value < node.Next->Data)
                {
                    node.Previous = node.Next;
                    node.Next = node.Next->Left;

                    node.Direction = NodeDirection::Left;
                }

                else if (value > node.Next->Data)
                {
                    node.Previous = node.Next;
                    node.Next = node.Next->Right;

                    node.Direction = NodeDirection::Right;
                }

               else
                   break;
            }

            return node;
        }

        void Delete(T value)
        {
            if (!this->Root)
                return;

            if (value == this->Root->Data)
                delete this->Root;

            NodePairInfo nodePair = this->GetNode(value);

            Node<T>* delNode; // temp pointer to the node that has to be deleted

            std::pair<Node<T>*, Node<T>*> smallestNode;


            if (!nodePair.Next)
                return;

            if (!nodePair.Next->Left && !nodePair.Next->Right) // If both children are null.
            {
                delete nodePair.Next;

                nodePair.Next = nullptr;
            }

            else if (!nodePair.Next->Left && nodePair.Next->Right) // Left child is null
            {
                delNode = nodePair.Next;

                this->Transplant(nodePair, nodePair.Next->Right);

                delete delNode;

                delNode = nullptr;
            }
            else if (nodePair.Next->Left && !nodePair.Next->Right) // Right child is null
            {
                delNode = nodePair.Next;

                this->Transplant(nodePair, nodePair.Next->Left);

                delete delNode;

                delNode = nullptr;
            }

            else if ((smallestNode = this->GetSmallest(nodePair.Next->Right)).second == nullptr)
            {
                smallestNode.first->Right = nullptr;

                smallestNode.second->Left = nodePair.Next->Left;
                smallestNode.second->Right = nodePair.Next->Right;

                nodePair.Previous->Right = smallestNode.second;

                delete nodePair.Next;
            }

            else
                switch (nodePair.Direction)
                {
                    case NodeDirection::Left:
                        smallestNode.second->Left = nodePair.Next->Left;
                        smallestNode.second->Right = nodePair.Next->Right;

                        delete nodePair.Previous->Left;

                        nodePair.Previous->Left = smallestNode.second;

                        break;

                   case NodeDirection::Right:
                        smallestNode.second->Left = nodePair.Previous->Right->Left;
                        smallestNode.second->Right = nodePair.Previous->Right->Right;

                        delete nodePair.Previous->Right;

                        nodePair.Previous->Right = smallestNode.second;

                        break;
                }
        }

        void Traverse()
        {
            this->TraverseInOrder(this->Root);
        }

        BinarySearchTree() : Root(nullptr)
        {
        }

        BinarySearchTree(T data)
        {
            this->Root = new Node<T>(data, nullptr, nullptr, nullptr); // Creates the node root.
        }

        BinarySearchTree(Node<T>* rootNode)
        {
            this->Root = rootNode; // Creates the node root.
        }

        ~BinarySearchTree()
        {
            this->Delete(this->Root);
        }
};

#endif // TREE_H
