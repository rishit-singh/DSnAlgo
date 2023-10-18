#ifndef HEAP_H_
#define HEAP_H_

#include <vector>
#include <iostream> 
#include <stdlib.h>

template<typename T>
using TraverseCallback = void(*)(T);

enum class HeapType 
{
	Max,
	Min
};

template<typename T>
inline void VectorSwap(std::vector<T>& vec, size_t index, size_t index1)
{	
	T temp = vec[index];

	vec[index] = vec[index1];
	vec[index1] = temp;
}

template<typename T>
inline void Swap(T& val, T& val1)
{
	T temp = val;

	val = val1;
	val1 = temp;
}

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

	size_t Size { 0 };

public:
	void Generate();

	const HeapType GetType() const;
	
	void SetType(HeapType);
	
	const size_t GetSize() const;

	void Traverse(const TraverseCallback<T>);
	
	void Traverse(const size_t, const TraverseCallback<T>);

	void Sort();

	Heap(const Heap<T>&);	

	Heap& operator =(const Heap<T>&);
	Heap& operator =(Heap<T>&&);

 	friend std::ostream& operator << <> (std::ostream& stream, const Heap<T>& heap);

	Heap(std::vector<T> = std::vector<T>(), HeapType = HeapType::Max);
	~Heap() = default;
};

template<typename T>
Heap<T>::Heap(std::vector<T> elements, HeapType type) : Type(type), Buffer(elements), Size(elements.size())
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
void Heap<T>::GenerateMax(size_t index)
{
	size_t left = this->GetLeft(index) - 1,
		   right =  this->GetRight(index) - 1,
		   largest;
			
	T value = this->Buffer[index - 1], 
	  max = Max<T>(Max<T>(this->Buffer[left], this->Buffer[right]), value); 	
		
	if (max == this->Buffer[left])
	{
		VectorSwap<T>(this->Buffer, left, index - 1);
		
		this->GenerateMax(left); 
	}
	else if (max == this->Buffer[right])
	{	
		VectorSwap<T>(this->Buffer, right, index - 1);
		
		this->GenerateMax(right);
	}
}

template<typename T>
void Heap<T>::GenerateMin(size_t index)
{
	T left = this->GetLeft(index),
	  right = this->GetRight(index),
	  value = this->Buffer[index];


	T min = Min<T>(Min<T>(left, right), value);

	if (min == left)
	{
		VectorSwap<T>(this->Buffer, left, index - 1);

		this->GenerateMin(left);
	}
	else if (min == right)
	{
		VectorSwap<T>(this->Buffer, right, index - 1);

		this->GenerateMin(right);
	}
}

template<typename T>
void Heap<T>::Generate() 
{
	if (this->Type == HeapType::Max)
		for (size_t x = this->Size / 2; x > 0; x--)
			this->GenerateMax(x);
	else
		for (size_t x = this->Size / 2; x > 0; x--)
			this->GenerateMin(x);
}

template<typename T>
const size_t Heap<T>::GetSize() const 
{
	return this->Size;
}


template<typename T>
void Heap<T>::Traverse(const TraverseCallback<T> callback) 
{
	this->Traverse(1, callback); 
}

template<typename T>
void Heap<T>::Traverse(const size_t index, const TraverseCallback<T> callback)
{
	if (index >=this->Size)
		return;

	this->Traverse(this->GetLeft(index), callback);
	
	callback(this->Buffer[index]);

	this->Traverse(this->GetRight(index), callback);
}

template<typename T>
void Heap<T>::Sort() 
{
	this->Generate();
		
	for (int x = this->Buffer.size() - 1; x > 0; x--)
	{
		VectorSwap<T>(this->Buffer, 0, x);
	
		this->GenerateMax(1);
	}	
}


template<typename T>
std::ostream& operator <<(std::ostream& stream, const Heap<T>& heap) 
{
	std::cout << "[ ";

	for (size_t x = 0; x < heap.Buffer.size() - 1; x++)
		stream << heap.Buffer[x] << ", ";

	stream << heap.Buffer[heap.Buffer.size() - 1] << " ]\n";

	return stream;
}
#endif
 
