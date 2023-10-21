#include "heap.h"

int main(int argc, char** argv)
{
	Heap<int> heap = Heap<int>({ 3, 4, 32, 12, 23, 54, 18, 5, 7, 10 }, HeapType::Max);

	heap.Generate();

//	heap.Traverse([](int value){ 
//				std::cout << value << " ";
//			});
	


	std::cout << heap;
	std::cout << '\n';
	
	heap.Sort();

	std::cout << heap;
	std::cout << '\n';


	return 0;
}
