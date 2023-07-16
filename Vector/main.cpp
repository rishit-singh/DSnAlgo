#include <iostream>
#include "vector.hpp"

int main(int argc, char** argv)
{
	Vector<int> vec = Vector<int>();

	
	for (int x = 0; x < 10; x++)
	{
		vec.Push(x);

		std::cout << "vec[" << x << "]: " << vec[x] << '\n';
	}

	return 0;
}


