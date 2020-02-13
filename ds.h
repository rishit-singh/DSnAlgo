#pragma once

#define DS_H
#define DS_H

#include <stdio.h>
#include <iostream>
#include <stack>
#include <string.h>
#include "algorithms.h"
#include "../cartesian.h"
using namespace std;
using namespace Algorithms;

namespace DataStructures
{
    typedef struct {
        int data;
        int* node;
    } linkedList;

    class Stack
    {
        #define MAX 1000
    public:
        Stack()
        {
            Stack::array = (int*) malloc(sizeof(int) * MAX);    
            Stack::count = 0;   
        }
        Stack(int size)
        {
            DataStructures::Stack::array = (int*) malloc(sizeof(int) * size);
            DataStructures::Stack::count = 0;       
        }
        static int* array;
        int top = -1; 
        static int count;
        static void Push(int val)
        {
            *(DataStructures::Stack::array + DataStructures::Stack::count) = val;
        }
        static exception* e;
        static void Pop()
        {
            *(DataStructures::Stack::array + DataStructures::Stack::count) = NULL;
        }

        static int* ToArray()
        {
            return DataStructures::Stack::array;
        }

        static int* ToArray(stack<int> s)
        {
            int* array = (int*) malloc(sizeof(int) * s.size());
            for (int x = 0; !(s.empty()); x++)
            {    
                *(array + x) = s.top();
                s.pop();
            }
            return array;
        }

        static Point* ToArray(stack<> s)
        {
            int* array = (int*) malloc(sizeof(int) * s.size());
            for (int x = 0; !(s.empty()); x++)
            {    
                *(array + x) = s.top();
                s.pop();
            }
            return array;
        }
    };
};


