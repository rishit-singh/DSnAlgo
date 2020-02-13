#include <iostream>
#include "ds.h"
#include <stack>
using namespace DataStructures;

int main()
{
	stack<int>* s = new stack<int>();
    for (int x = 0; x < 10; x++)
		s->push(x);


	cout << *(DataStructures::Stack::ToArray(*s) + 0);
    
}