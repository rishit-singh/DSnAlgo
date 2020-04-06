#pragma once

#define COMPRESSSION_H
#define COMPRESSSION_H

#include <iostream>
#include <string>
#include <stack>

class Compresssor
{
private:
    struct charRecursion
    {
        int freq;
        char ch;
    };

    stack<struct charRecursion> chr;

public: 
    static char* Compress(char* data)
    {
        char c;
        int count = 0;

        for (int x = 0; x < strlen(data); x++)
        {
            struct charRecursion chiTemp;
            
            if ((c = *(data + x)) == *(data + (x + 1))
            {
                chr.chr = c;
                count++;
                chr.freq = count;
            }
            else
            {
                chr.chr = c = *(data + x);
                chr.freq = 1;
            }

            stack.push(chr); 
            
            count = 0;
        }
    }
};


int main()
{
    char* str = "Hello World!";
    cout << "Original:"
        << str
        << "\nCompressed:" 
        <<Compresssor.Compress("Hello World!");
    return 0;
}
