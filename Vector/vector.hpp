#ifndef VECTOR_H_
#define VECTOR_H_


#include <cstdlib>
#include <stdexcept>
#include <initializer_list>

template<typename T>
using SortFunction = void (*)(T*, const size_t);

template<typename T>
void Swap(T& a, T& b)
{
	T temp = a;
	
	a = b;
	b = temp;
}

template<typename T>
void Sort(T*, size_t);

template<typename T, size_t = 1024, SortFunction<T> = Sort>
class Vector
{
private:
    void Initialize(std::initializer_list<T>&);

	void Resize(size_t);
	void Expand(size_t);
	void Shrink(size_t);
	
	const int Search(T);
	void Sort();
	
	size_t Size;
	
	size_t Count;

	T* Buffer;

	bool IsSorted;
public:
		
    const size_t Push(T);
   	void Push(const Vector<T>&);

    const T Pop();
    const T Remove(const size_t);
    const T Remove(T);
	T& At(const size_t);
	
    Vector<T>& operator =(const Vector<T>&);
    Vector<T>& operator =(Vector<T>&&);

	T& operator [](size_t);

	const T* GetData() const;
	const size_t GetCount() const; 
	const size_t GetSize() const;

	T* Discard();

	Vector();
	Vector(std::initializer_list<T>);
    Vector(const Vector<T>&);
    Vector(Vector<T>&&);
    ~Vector();
};


#endif // VECTOR_H_
