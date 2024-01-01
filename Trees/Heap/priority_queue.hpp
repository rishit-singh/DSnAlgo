#ifndef PRIORITYQUEUE_H_
#define PRIORITYQUEUE_H_

#include <cstdlib>
#include <unordered_map>
#include <stdexcept>
#include "heap.h"

template<typename T = uint32_t>
class PriorityQueue;

template<typename T>
struct KeyValue
{
	int Key;

	T Value;

	KeyValue(const int = 0, const T = nullptr);
}; 

template<typename T>
KeyValue<T>::KeyValue(const int key, const T value) : Key(key), Value(value)
{}

template<typename T>
class PriorityQueue
{
private:
	friend class Heap<T>;	

	Heap<T> MaxHeap;	

	std::unordered_map<int, size_t> IndexMap;

	T GetHeapMax() const;

	T ExtractHeapMax(); 
public:
	
	void Insert(KeyValue<T>); 
	void IncreaseKey(KeyValue<T>, int);

	PriorityQueue() = default;
	~PriorityQueue() = default;
};

template<typename T>
T PriorityQueue<T>::GetHeapMax() const
{
	if (this->MaxHeap.GetSize() < 1)
		throw std::runtime_error("Heap underflow");


	return this->MaxHeap[0];
}

template<typename  T>
T PriorityQueue<T>::ExtractHeapMax()
{
	T max = this->GetHeapMax();

	this->MaxHeap.Buffer[0] = this->MaxHeap[this->MaxHeap.GetSize() - 1];

	this->MaxHeap.Size--;

	this->MaxHeap.GenerateMax(0);
	
	return max;
}

template<typename T>
void PriorityQueue<T>::IncreaseKey(KeyValue<T> object, int key)
{
}

#endif
