#ifndef PRIORITYQUEUE_H_
#define PRIORITYQUEUE_H_

#include <cstdlib>
#include <unordered_map>
#include <stdexcept>
#include <iterator>
#include <initializer_list>
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

	std::unordered_map<KeyValue<T>, size_t> IndexMap;

	T GetHeapMax() const;

	[[nodiscard]] T ExtractHeapMax();

	std::vector<KeyValue<T>> Buffer;
public:
	void Insert(KeyValue<T>); 
	void IncreaseKey(KeyValue<T>, int);
	
	PriorityQueue(std::initializer_list<KeyValue<T>> = {}) noexcept;
	~PriorityQueue() = default;
};

template<typename T>
PriorityQueue<T>::PriorityQueue(std::initializer_list<KeyValue<T>> initial) noexcept :
	Buffer(initial), MaxHeap(initial, HeapType::Max)
{
	this->MaxHeap.Generate();
}

template<typename T>
void PriorityQueue<T>::IncreaseKey(KeyValue<T> object, int key)
{		
	if (key < object.Key)
		throw std::runtime_error("Provided key is smaller than the existing key.");

	size_t index = std::distance(this->MaxHeap.begin(), this->MaxHeap.Find(object.Value));
	
//	for (; index >= 0 && this->MaxHeap.GetParent(); )
}

#endif
