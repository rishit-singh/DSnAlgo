#include "heap.h"

int main(int argc, char** argv)
{
	Heap<int> heap = Heap<int>({ 3, 4, 32, 12, 23, 54, 18, 5, 7, 10 }, HeapType::Max);

	heap.Generate();
	
	for (auto val : heap)
		std::cout << val << " ";
	
	heap.Sort();

	std::cout << "\n";

	for (auto val : heap)
		std::cout << val << " ";
	
	std::cout << "\n";

	heap.Delete(12);

	std::cout << heap << '\n';
	
	heap.Insert(69);

	std::cout << heap << '\n';

	return 0;
}
 
