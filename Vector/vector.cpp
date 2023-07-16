#include "vector.hpp"

template <typename T>
void Sort(T *array, size_t size)
{
	
}

template <typename T, size_t ChunkSize, SortFunction<T> Sort>
void Vector<T, ChunkSize, Sort>::Resize(size_t size)
{
	T* temp = this->Buffer;

	this->Buffer = new T[size];

	for (int x = 0; x < size; x++)		
		this->Buffer[x] = temp[x];

	this->Size = size; 
}

template <typename T, size_t ChunkSize, SortFunction<T> Sort>
void Vector<T, ChunkSize, Sort>::Expand(size_t size)
{
	this->Resize(this->Size + size);
}

		
template <typename T, size_t ChunkSize, SortFunction<T> Sort>
void Vector<T, ChunkSize, Sort>::Shrink(size_t size)
{
	if ((this->Size - size) < 0)
		throw std::runtime_error("Shrink size out of range.");

	this->Resize(this->Size - size);
}

		
template <typename T, size_t ChunkSize, SortFunction<T> Sort>
const size_t Vector<T, ChunkSize, Sort>::Push(T value)
{
	if (this->Count >= this->Size)
		this->Expand(ChunkSize);	
	
	this->Buffer[Count] = value; 

	return (this->Count++);
}

template <typename T, size_t ChunkSize, SortFunction<T> Sort>
void Vector<T, ChunkSize, Sort>::Push(const Vector<T>& values)
{
	for (int x = 0 ; x < values.size(); x++)
		this->Push(values[x]);
}

template <typename T, size_t ChunkSize, SortFunction<T> Sort>
const T Vector<T, ChunkSize, Sort>::Pop()
{
	if (this->Count < 1)
		throw std::runtime_error("Can't pop an empty Vector.");

	T popped = Buffer[Count];	

	this->Buffer[--Count] = 0;

	
	if ((Size - Count) >= ChunkSize)
		this->Shrink(ChunkSize);

	
	return popped;
}	

template <typename T, size_t ChunkSize, SortFunction<T> Sort>
const T Vector<T, ChunkSize, Sort>::Remove(size_t index)
{
	if (index >= this->Count)
		throw std::runtime_error("Index out of range.");

	T popped = Buffer[index];	

	this->Buffer[index] = 0;

	Swap<T>(Buffer[index], Buffer[--this->Count]); 

	if ((Size - Count) >= ChunkSize)
		this->Shrink(ChunkSize);
	
	return popped;
}

template <typename T, size_t ChunkSize, SortFunction<T> Sort>
const T Vector<T, ChunkSize, Sort>::Remove(T value)
{	
	int index;
	

	if ((index = this->Search(value)) == -1)
		return 0;

	T popped = Buffer[index];	

	this->Buffer[index] = 0;

	Swap<T>(Buffer[index], Buffer[--this->Count]); 

	if ((Size - Count) >= ChunkSize)
		this->Shrink(ChunkSize);

	return popped;
}

template <typename T, size_t ChunkSize, SortFunction<T> Sort>
T& Vector<T, ChunkSize, Sort>::At(const size_t index)
{
	if (index >= this->Count)
		throw std::runtime_error("Index out of range.");

	return this->Buffer[index];
}

template <typename T, size_t ChunkSize, SortFunction<T> Sort>
void Vector<T, ChunkSize, Sort>::Initialize(std::initializer_list<T>& list)
{
	for (int x = 0 ; x < list.size(); x++)
		this->Push(list);
}


template <typename T, size_t ChunkSize, SortFunction<T> Sort>
const T* Vector<T, ChunkSize, Sort>::GetData() const
{
	return this->Buffer;
}

template <typename T, size_t ChunkSize, SortFunction<T> Sort>
const size_t Vector<T, ChunkSize, Sort>::GetSize() const
{
	return this->Size;
}

template <typename T, size_t ChunkSize, SortFunction<T> Sort>
const size_t Vector<T, ChunkSize, Sort>::GetCount() const
{
	return this->Count;
}

template <typename T, size_t ChunkSize, SortFunction<T> Sort>
T* Vector<T, ChunkSize, Sort>::Discard()
{
	T* temp = this->Buffer;

	this->Buffer = nullptr;

	return temp;
}


template <typename T, size_t ChunkSize, SortFunction<T> Sort>
T& Vector<T, ChunkSize, Sort>::operator [](const size_t index)
{
	return this->At(index);
}

template <typename T, size_t ChunkSize, SortFunction<T> Sort>
Vector<T>& Vector<T, ChunkSize, Sort>::operator =(const Vector<T>& vector)
{
	this->Expand(vector.GetSize());
	this->Push(vector);	

	return *this;
}

template <typename T, size_t ChunkSize, SortFunction<T> Sort>
Vector<T>& Vector<T, ChunkSize, Sort>::operator =(Vector<T>&& vector)
{
	this->Buffer = vector.Discard();
	this->Size = vector.GetSize();
	this->Count  =vector.GetCount();

	return *this;
}

template <typename T, size_t ChunkSize, SortFunction<T> Sort>
Vector<T, ChunkSize, Sort>::Vector() : Size(0), Count(0), IsSorted(false) 
{
}

template <typename T, size_t ChunkSize, SortFunction<T> Sort>
Vector<T, ChunkSize, Sort>::Vector(std::initializer_list<T> list) : Size(0), Count(0), IsSorted(false) 
{
	this->Expand(ChunkSize);
	this->Initialize(list);
} 

template <typename T, size_t ChunkSize, SortFunction<T> Sort>
Vector<T, ChunkSize, Sort>::Vector(const Vector<T>& vector) : Size(0), Count(0), IsSorted(false) 
{
	this->Expand(vector.GetSize());
	this->Push(vector);	
}

template <typename T, size_t ChunkSize, SortFunction<T> Sort>
Vector<T, ChunkSize, Sort>::Vector(Vector<T>&& vector) : Size(0), Count(0), IsSorted(false) 
{
	this->Buffer = vector.Discard();
	this->Size = vector.GetSize();
	this->Count  =vector.GetCount();
}

template <typename T, size_t ChunkSize, SortFunction<T> Sort>
Vector<T, ChunkSize, Sort>::~Vector()
{	
	delete this->Buffer;
	this->Buffer = nullptr;
}


