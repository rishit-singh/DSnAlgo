#ifndef SORT_H
#define SORT_H

#include <stdlib.h>

template<typename T>
static void Swap(T* val, T* val1)
{
    T temp = *val;

    *val = *val1;
    *val1 = temp;
}

enum class SortingAlgorithm
{
    QuickSort
};

template<typename T>
class Sorting
{
private:
    static int Partition(T* array, unsigned int start, unsigned int end)
    {
        T pivot = array[end];

        int i = start - 1;

        for (int x = start; x < end; x++)
            if (array[x] <= pivot)
            {
                i++;

                Swap<T>(&array[i], &array[x]);
            }

        Swap<T>(&array[++i], &array[end]);

        return i;
    }

    static T* QuickSort(T* array, unsigned int start, unsigned int end)
    {
        int q;

        if (start < end)
        {
            q = Sorting::Partition(array, start, end);

            QuickSort(array, start, q - 1);
            QuickSort(array, q + 1, end);
        }

        return array;
    }

public:
        static inline SortingAlgorithm DefaultSortingAlgorithm = SortingAlgorithm::QuickSort;

        static T* Sort(T* array, size_t size)
        {
            return Sorting<T>::Sort(array, size, Sorting::DefaultSortingAlgorithm);
        }

        static T* Sort(T* array, size_t size, SortingAlgorithm algo)
        {
            switch (algo)
            {
                case SortingAlgorithm::QuickSort:
                    Sorting::QuickSort(array, 0, size - 1);

                    break;

                default:
                    return nullptr;
            }

            return array;
        }
};

#endif // SORT_H_
