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

            NodePairInfo() : Previous(nullptr), Next(nullptr), Direction(NodeDirection::Left)
            {
            }

            NodePairInfo(Node<T>* prev, Node<T>* next, BinarySearchTree::NodeDirection nodeDirection) : Previous(prev), Next(next), Direction(nodeDirection)
            {
            }
        };

        NodePairInfo GetSmallest(Node<T>* node)
        {
            if (!node)
                return NodePairInfo(nullptr, nullptr, NodeDirection::Left);

            Node<T>* parent = node;

            while (node->Left)
            {
                parent = node;

                node = node->Left;
            }

            return NodePairInfo(parent, node, NodeDirection::Left);
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

            NodePairInfo nodePair = this->GetNode(value),
                smallestNode;

            Node<T>* delNode; // temp pointer to the node that has to be deleted

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

            else if ((smallestNode = this->GetSmallest(nodePair.Next->Right)).Next == nullptr)
            {
                smallestNode.Previous->Left = nullptr;

                smallestNode.Next->Left = nodePair.Next->Left;
                smallestNode.Next->Right = nodePair.Next->Right;

                nodePair.Previous->Right = smallestNode.Next;

                delete nodePair.Next;
            }

            else
            {
                smallestNode.Next->Left = nodePair.Next->Left;
                smallestNode.Next->Right = nodePair.Next->Right;

                switch (nodePair.Direction)
                {
                    case NodeDirection::Left:

                        delete nodePair.Previous->Left;

                        nodePair.Previous->Left = smallestNode.Next;

                        break;

                   case NodeDirection::Right:

                        delete nodePair.Previous->Right;

                        nodePair.Previous->Right = smallestNode.Next;

                        break;
                }
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
