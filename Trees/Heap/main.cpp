#include "heap.h"

int main(int argc, char** argv)
{
	Heap<int> heap = Heap<int>({ 3, 4, 32, 12, 23, 54, 18, 5, 7, 10 }, HeapType::Min);

	heap.Generate();
	
	for (auto val : heap)
		std::cout << val << " ";
	
	heap.Sort();

	std::cout << "\n";

	for (auto val : heap)
		std::cout << val << " ";

	return 0;
}
 
