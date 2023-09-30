#include "heap.h"

int main(int argc, char** argv)
{
	Heap<int> heap = Heap<int>({ 3, 4, 32, 12, 23, 54, 18, 5, 7 }, HeapType::Max);

	heap.Generate();

	std::cout << heap;

	return 0;
}
