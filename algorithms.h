#pragma once

#define ALGORITHMS_H
#define ALGORITHMS_H

#include <stdio.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>

namespace Algorithms
{   
    // template <typename T>
    // class Randoms
    // {
    // public:
    //     static int ArrayLength(T* array)
    //     {
    //         for (int x = 0; *(array + x) != NULL; x++);
    //         return x;
    //     }
    // };

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
};