#pragma once

#define DS_H
#define DS_H

#include <stdio.h>
#include <iostream>
#include <string.h>
#include "algorithms.h"

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
    private:
        #define MAX 1000
        int* array = (int*) malloc(sizeof(int) * MAX);
        int top = -1; 
    public:
        static void Push(int val)
        {
            *(array + count) = val;
        }

        static void Push(int* arr)
        {
            strcpy(arr, *(array + count);
            count++;
        } 

        static void Pop()
        {
            *(array + count) = NULL;
        }

        static int* ToArray()
        {
            return array;
        }
    };
};