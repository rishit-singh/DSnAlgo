#ifndef HEAP_H_
#define HEAP_H_

#include <vector>
#include <stdlib.h>

enum class HeapType 
{
	Max,
	Min
};

template<typename T = uint32_t>
class Heap 
{
private:
	void GenerateMax();	
	void GenerateMin();

	T GetParent(size_t);
	T GetLeft(size_t);
	T GetRight(size_t);

	HeapType Type;
	
	std::vector<T> Buffer;

	size_t Size;

public:
	void Generate();

	const HeapType GetType() const;
	
	void SetType(HeapType);
	
	const size_t GetSize() const;

	Heap(std::vector<T> = std::vector<T>(), HeapType = HeapType::Max);
	~Heap() = default;
};

template<typename T>
Heap<T>::Heap(std::vector<T> elements, HeapType type) : Type(type)
{
}

template<typename T>
void Heap<T>::SetType(HeapType type) 
{
	this->Type = type;
}

template<typename T>
const HeapType Heap<T>::GetType() const
{
	return this->Type;
}

template<typename T>
T Heap<T>::GetParent(size_t index)
{
	return index / 2;
} 

template<typename T>
T Heap<T>::GetLeft(size_t index)
{
	return index * 2;
} 

template<typename T>
T Heap<T>::GetRight(size_t index)
{
	return (index * 2) + 1;
} 

template<typename T>
void Heap<T>::GenerateMax()
{
}

template<typename T>
void Heap<T>::GenerateMin()
{
}

template<typename T>
void Heap<T>::Generate() 
{
}

template<typename T>
const size_t Heap<T>::GetSize() const 
{
	return this->Size;
}

#endif


