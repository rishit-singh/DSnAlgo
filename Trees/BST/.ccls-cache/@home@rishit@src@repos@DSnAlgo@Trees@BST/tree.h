// Tree implementations.

#ifndef TREE_H
#define TREE_H

#define DEBUG

#include "node.h"
#include <cinttypes>
#include <iostream>
#include <utility>

/*
* Safe deletes the value at the provide pointer.
*/
template<typename T>
static void DeletePointer(T* p)
{
    if (!p) // null check
        return;

    delete p;

    p = nullptr;
}

// Stores the binary tree nodes and related functions.
template<typename T>
class BinarySearchTree
{
private:
        Node<T>* TraverseInOrder(Node<T>* node)
        {
            if (node == nullptr)
                return node;

            TraverseInOrder(node->Left);

            #ifdef DEBUG
            std::cout << " " << node->Data << " ";
            #endif

            TraverseInOrder(node->Right);

            return node;
        }

        // void TraversePostOrder(T* array, size_t size)
        // {
        // }

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

        void DeleteNode(Node<T>* node)
        {
            DeletePointer<Node<T>>(node);
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

            BinarySearchTree::NodeDirection Direction; // Direction in which Next succeeds Previous

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

                else if (value < current->Data)
                    current = current->Left;

                else if (value > current->Data)
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

            while (node.Next) // Runs until next node is null.
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
            NodePairInfo node = this->GetNode(value), successor;

            Node<T>* delNode = node.Next; // node to be deleted

            if (delNode == this->Root)
                this->DeleteNode(delNode);

            else if (!delNode.Next)
                return;

            else if (!node.Next.Left && !node.Next.Right) // both children are null
                this->DeleteNode(delNode);

            else if (!node.Next.Left && node.Next.Right)
            {
                this->Transplant(node, node.Next.Right);
                this->DeleteNode(delNode);
            }

            else if (node.Next.Left && !node.Next.Right)
            {
                this->Transplant(node, node.Next.Left);
                this->DeleteNode(delNode);
            }

            else
                if (!((successor = this->GetSmallest(node.Right).Next)))
                {
                    this->Transplant(node, node.Right);
                    this->DeleteNode(delNode);
                }
                else
                {
                    this->Transplant(node, successor.Next);
                    this->DeleteNode(delNode);
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
