#pragma once

#define ALGORITHMS_H
#define ALGORITHMS_H

#include <stdio.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include "exceptions.h"

#define DEFAULT_ARRAY_SIZE 100000

using namespace std;
using namespace ErrorHandler;

namespace Algorithms
{   
    // template <typename>
    class Randoms
    {
    public:
        static char* Concatenate(char* string0, char* string1)
        {
            char* FinalStr = (char*)malloc(sizeof(char) * DEFAULT_ARRAY_SIZE);

            strcpy(string0, FinalStr);

            for (int x = 0; *(string1 + x) != EOF; x++)
                *((FinalStr + strlen(FinalStr)) + x) = *(string1 + x);

            return FinalStr;
        }

        static void PrintArray(int* array)
        {
            for (int x = 0; x < sizeof(array) / sizeof(int); x++)
                cout << *(array + x) << " ";
        }

        static void Swap(int* a, int* b)
        {
            int temp = *a;
            *a = *b; 
            *b = temp;
        }

        static int ArrayLength(int* array)
        {
			int len;

            for (len = 0; *(array + len) != NULL; len++);

			return len;
        }
    };

    class Cryptography
    {
        #define ENCRYPTLIMIT 100000000
    public:
        static char* Encrypt(char* str)
        {
            char* encryptedStr = (char*) malloc(sizeof(char) * ENCRYPTLIMIT);
            int len;
            
			for (int x = 0; x < (len = strlen(str)); x++)
            {
                *(encryptedStr + x) = (char)((int)*(str + x) + (int)(((len > 30) ? len - (len - 30) : len) / 3));
            }

            return encryptedStr;
        }

        static char* Decrypt(char* encryptedStr) 
        {   
            char* decryptedStr = (char*) malloc(sizeof(char) * ENCRYPTLIMIT);
            int len;
            
			for (int x = 0; x < (len = strlen(encryptedStr)); x++)
            {
                *(decryptedStr + x) = (char)((int)*(encryptedStr + x) - (int)(((len > 30) ? len - (len - 30) : len) * 3));
            }

            return decryptedStr;

        }
    };

    class Sort
    {
    public: 
        enum Criteria
        {
            Ascending = 1,
            Descending = -1
        };

        static int* BubbleSort(int* array, Sort::Criteria criteria)
        {
            switch (criteria)
            {
                case Sort::Ascending:
                    for (int x = 0; x < Randoms::ArrayLength(array) / 2; x++)
                        if (*(array + x) > *(array + (x + 1)))
                            Randoms::Swap(array + x, array + (x + 1));
                    break;

                case Sort::Descending:
                    for (int x = 0; x < Randoms::ArrayLength(array) / 2; x++)
                        if (*(array + x) < *(array + (x + 1)))
                            Randoms::Swap(array + x, array + (x + 1));
                    break;
            } 
        }

        static int* BubbleSort(int* array, int criteria) //overload for intger criteria
        {
            try
            {
                switch ((Sort::Criteria)criteria)
                {
                    case Sort::Ascending:
                        for (int x = 0; x < Randoms::ArrayLength(array) / 2; x++)
                            if (*(array + x) > *(array + (x + 1)))
                                Randoms::Swap(array + x, array + (x + 1));
                        break;

                    case Sort::Descending:
                        for (int x = 0; x < Randoms::ArrayLength(array) / 2; x++)
                            if (*(array + x) < *(array + (x + 1)))
                                Randoms::Swap(array + x, array + (x + 1));
                        break;
                    default:
                        throw (ErrorHandler::InvalidSortCriteria); 
                }
            }
            catch (Exception InvalidSortCriteria)
            {
                std::cout << "Error: InvalidSortCriteria exception thrown.";   //for now
            }
        }
    
        static int* InsertionSort(int* array, Sort::Criteria criteria)
        {
            int key, j;

            try
            {
                switch (criteria)
                {
                    case Sort::Ascending:
                        for (int x = 1; x < sizeof(array) / sizeof(int); x++ )
                        {
                            key = *(array + x);
                            j = x - 1; 

                            while (j >= 0 && *(array + x) > key)
                            {
                                *(array + (j + 1)) = *(array + j);
                                j -= 1;
                            }
                            
                            *(array + j) = key;
                        }

                        break;
                    
                    case Sort::Descending:
                        for (int x = 1; x < sizeof(array) / sizeof(int); x++ )
                        {
                            key = *(array + x);
                            j = x - 1; 

                            while (j >= 0 && *(array + x) < key)
                            {
                                *(array + (j + 1)) = *(array + j);
                                j -= 1;
                            }
                            
                            *(array + j) = key;
                        }

                        break;
                    
                    default:
                        throw (InvalidSortCriteria);
                }
            }
            catch (Exception e)
            {
               cout << e.Message;
            }
        }
        static int* InsertionSort(int* array, int criteria);
    };

    class Search
    {
    public:
        static int BinarySearch(int val, int* array, int start, int end)
        {
            int* arr = Sort::BubbleSort(array, Sort::Ascending); //sorted array
			int n = Randoms::ArrayLength(arr), mid = start + (end - 1) / 2, element = *(arr + mid);

			if (end >= start)
			{
				if (element == val)
					return element;

            	if (element > val)
					return BinarySearch(val, arr, 0, mid - 1);

				return BinarySearch(val, arr, mid + 1, end);
           	}
			
			return -1;
		}

		static int LinearSearch(int val, int* array)
		{
			int index; 

			for (index = 0; *(array + index) != NULL; index++)
				if (*(array + index) == val)
					return index; 
			
			return index;
		}
    };
};