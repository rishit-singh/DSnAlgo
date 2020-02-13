#include <iostream>
#include "ds.h"

using namespace DataStructures;

int main()
{
    DataStructures::Stack* s = new Stack(10);
    for (int x = 0; x < 10; x++)
    {    
        s->Push(x);
        std::cout << s->top;
    }
}