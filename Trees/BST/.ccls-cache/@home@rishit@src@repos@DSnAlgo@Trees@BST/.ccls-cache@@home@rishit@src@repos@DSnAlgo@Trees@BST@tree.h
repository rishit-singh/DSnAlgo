// Tree implementations.

#ifndef TREE_H
#define TREE_H

#define DEBUG

#include "node.h"
#include <cinttypes>
 <utility>

#ifdef DEBUG
#include <iostream>
#endif

/*
* Safely deletes the value at the provide pointer.
*/
template<typename T>
static void DeletePointer(T*& p)
{
    if (!p) // null check
        return;

    delete p;

    p = nullptr;
}

// Stores the binary tree nodes and related functions.
template <typename T> class BinarySearchTree {
private:
  Node<T> *TraverseInOrder(Node<T> *node) {
    if (node == nullptr)
      return node;

    TraverseInOrder(node->Left);

    //#ifdef DEBUG
    std::cout << " " << node->Data << " ";
    //#endif

    TraverseInOrder(node->Right);

    return node;
  }

  void Delete(Node<T> *node) // Deletes all the nodes from the current instance
                             // of the tree.
  {
    if (!node)
      return;

    Delete(node->Left);
    Delete(node->Right);

    delete node;
  }

  void DeleteNode(Node<T> *node) { DeletePointer<Node<T>>(node); }
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
                    *Current;

            BinarySearchTree::NodeDirection Direction; // Direction in which Current succeeds Previous

            NodePairInfo operator =(NodePairInfo& nodePairInfo)
            {
                return NodePairInfo(nodePairInfo);
            }

            NodePairInfo operator  =(NodePairInfo nodePairInfo)
            {
                return NodePairInfo(nodePairInfo);
            }

            NodePairInfo() : Previous(nullptr), Current(nullptr), Direction(NodeDirection::Left)
            {
            }

            NodePairInfo(Node<T>* prev, Node<T>* current, BinarySearchTree::NodeDirection nodeDirection) : Previous(prev), Current(current), Direction(nodeDirection)
            {
            }

            NodePairInfo(NodePairInfo& nodePairInfo) : Current(nodePairInfo.Current), Previous(nodePairInfo.Previous), Direction(nodePairInfo.Direction)
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

        // Replaces the Current node of the provided NodePairInfo with the substituteNode
        void Transplant(NodePairInfo& nodePair, Node<T>* substituteNode)
        {
            if (!substituteNode)
                return;

            switch (nodePair.Direction)
            {
                case NodeDirection::Left:
                    substituteNode->Left = nodePair.Current->Left;
                    substituteNode->Right = nodePair.Current->Right;

                    nodePair.Previous->Left = substituteNode;

                    break;

                case NodeDirection::Right:
                    substituteNode->Left = nodePair.Current->Left;
                    substituteNode->Right = nodePair.Current->Right;

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

            while (node.Current && node.Current->Data != value) // Runs until current node is null.
                if (value < node.Current->Data)
                {
                    node.Previous = node.Current;
                    node.Current = node.Current->Left;

                    node.Direction = NodeDirection::Left;
                }

                else if (value > node.Current->Data)
                {
                    node.Previous = node.Current;
                    node.Current = node.Current->Right;

                    node.Direction = NodeDirection::Right;
                }


            return node;
        }

        void Delete(T value)
        {
            NodePairInfo node = this->GetNode(value), successor;

            Node<T>* delNode = node.Current; // node to be deleted

            if (value == this->Root->Data)
                this->DeleteNode(delNode);

            else if (!node.Current) // node doesnt exist
            {
                //#ifdef DEBUG
                std::cout << "Node doent exist.\n";
                //#endif
            }

            else if (!node.Current->Right)
            {
                this->Transplant(node, node.Current->Left);
                this->DeleteNode(delNode);
            }

            else
                if (!node.Current->Right->Left) // No smaller child
                {
                    node.Current->Right->Left = node.Current->Left;

                    switch (node.Direction)
                    {
                        case NodeDirection::Left:
                            node.Previous->Left = node.Current->Right;

                            break;

                        case NodeDirection::Right:
                            node.Previous->Right = node.Current->Right;

                            break;
                    }

                    //this->Transplant(node, node.Current->Right);
                    this->DeleteNode(node.Current);

                    return;
                }
                else
                {
                    successor = this->GetSmallest(node.Current->Right);

                    // successor.Previous->Left = nullptr;

                    this->Transplant(node, successor.Current);
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
