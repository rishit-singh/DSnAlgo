#ifndef HEAP_H_
#define HEAP_H_

#include <vector>
#include <iostream> 
#include <stdlib.h>
#include <iterator>
#include <algorithm>

enum class HeapType 
{
	Max,
	Min
};

template<typename T>
T Max(T a, T b)
{
	return (a > b) ? a : b;
}

template<typename T>
T Min(T a, T b)
{
	return (a < b) ? a : b;
}

template<typename T = uint32_t>
class Heap ;

template<typename T = uint32_t>
std::ostream& operator << (std::ostream& stream, const Heap<T>& heap);

template<typename T>
using TraverseCallback = std::function<void(T)>;   

template<typename T>
class Heap 
{
private:
	void GenerateMax(size_t);	
	void GenerateMin(size_t);

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

	void Traverse(const TraverseCallback<T>) const noexcept;
	
	void Traverse(const size_t, const TraverseCallback<T>) const noexcept;

	void Sort();

	std::vector<T>::iterator begin(); 
	std::vector<T>::iterator end(); 

	[[nodiscard]] std::vector<T>::iterator Find(T) const noexcept;

	Heap(const Heap<T>&) = default;
	Heap(Heap<T>&&) = default;

	Heap& operator =(const Heap<T>&);
	Heap& operator =(Heap<T>&&);

	friend std::ostream& operator << <> (std::ostream& stream, const Heap<T>& heap);

	T& operator [](const size_t) const;

	Heap(const std::vector<T> = { }, HeapType = HeapType::Max);
	~Heap() = default;
};
 
template<typename T>
Heap<T>::Heap(const std::vector<T> elements, HeapType type) : Type(type), Buffer(elements), Size(elements.size())
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
	return (index - 1) / 2;
} 

template<typename T>
T Heap<T>::GetLeft(size_t index)
{
	return (index * 2) + 1;
} 

template<typename T>
T Heap<T>::GetRight(size_t index)
{
	return (index * 2) + 2;
} 
 
template<typename T>
void Heap<T>::GenerateMax(size_t index)
{
	size_t left = this->GetLeft(index),
		   right = this->GetRight(index),
		   largest; 
		
	T value = this->Buffer[index]; 
		
	if (left < this->Size && this->Buffer[left] > value)
		largest = left;
	else
		largest = index;

	if (right < this->Size && this->Buffer[right] > this->Buffer[largest])
		largest = right;
	
	if (largest != index)
	{
		std::swap(this->Buffer[largest], this->Buffer[index]);

		this->GenerateMax(largest);
	}
}

template<typename T>
void Heap<T>::GenerateMin(size_t index)
{
	T left = this->GetLeft(index),
	  right = this->GetRight(index),
	  value = this->Buffer[index],
	  smallest = index;

	if (left < this->Size && this->Buffer[left] < value)
		smallest = left;

	if (right < this->Size && this->Buffer[right] < this->Buffer[smallest])
		smallest = right;

	if (smallest != index)
	{
		std::swap(this->Buffer[smallest], this->Buffer[index]);


		this->GenerateMin(smallest);
	}
}

template<typename T>
void Heap<T>::Generate() 
{
	if (this->Type == HeapType::Max)
		for (int x = (this->Size / 2) - 1; x >= 0; x--)
			this->GenerateMax(x);
	else
		for (int x = (this->Size / 2) -  1; x >= 0; x--)
			this->GenerateMin(x);
}

template<typename T>
const size_t Heap<T>::GetSize() const 
{
	return this->Size;
}

template<typename T>
void Heap<T>::Traverse(const TraverseCallback<T> callback) const noexcept
{
	this->Traverse(1, callback); 
} 

template<typename T>
void Heap<T>::Traverse(const size_t index, const TraverseCallback<T> callback) const noexcept 
{
	if (index >= this->Size)
		return;

	this->Traverse(this->GetLeft(index), callback);
	
	callback(this->Buffer[index]);

	this->Traverse(this->GetRight(index), callback);
}

template<typename T>
void Heap<T>::Sort() 
{
	this->Generate(); 
	
	for (int x = this->Size - 1; x >= 1; x--)
	{
		std::swap(this->Buffer[0], this->Buffer[x]);

		this->Size--;

		this->GenerateMax(0);
	}
}


template<typename T>
[[nodiscard]] std::vector<T>::iterator Heap<T>::Find(T val) const noexcept
{
	std::vector<T>::iterator it;

	for (it = this->begin(); it != this->end() || *it != val; it++);

	return it;
}

template<typename T>
std::ostream& operator <<(std::ostream& stream, const Heap<T>& heap) 
{
	std::cout << "[ ";
 
	for (size_t x = 1; x < heap.Buffer.size() - 1; x++)
		stream << heap.Buffer[x] << ", ";

	stream << heap.Buffer[heap.Buffer.size() - 1] << " ]\n";

	return stream;
}

template<typename T>
T& Heap<T>::operator [](const size_t index) const
{
	return this->Buffer[index];
}

template<typename T>
std::vector<T>::iterator Heap<T>::begin() 
{
	return this->Buffer.begin();
}

template<typename T>
std::vector<T>::iterator Heap<T>::end() 
{
	return this->Buffer.end();
}

#endif

