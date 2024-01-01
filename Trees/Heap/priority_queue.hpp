#ifndef PRIORITYQUEUE_H_
#define PRIORITYQUEUE_H_

#include <cstdlib>
#include <unordered_map>
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
	
	T GetHeapMax() const;

	T ExtractHeapMax(); 
public:
	
	void Insert(); 
	void IncreaseKey(KeyValue<T>, int key);

	PriorityQueue() = default;
	~PriorityQueue() = default;
};


#endif
