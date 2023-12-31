#include "heap.h"

int main(int argc, char** argv)
{
	Heap<int> heap = Heap<int>({ 3, 4, 32, 12, 23, 54, 18, 5, 7, 10 }, HeapType::Max);

	heap.Generate();

	std::cout << heap;
	std::cout << '\n';
	
	heap.Sort();
	
	for (auto val : heap)
		std::cout << val << " ";

	std::cout << '\n';


	return 0;
}

