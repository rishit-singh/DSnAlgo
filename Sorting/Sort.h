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

    static void Merge(T* array, const size_t l, const size_t m, const size_t r)
    {
        int n = m - l,
            n1 = r - m;

        T left[n], right[n1];

        int x, y, z;

        for (int i = 0; i < n; i++)
            left[i] = array[l + i];

        for (int i = 0; i < n1; i++)
            right[i] = array[i + m + 1];

        for (x = 0, y = 0, z = 0; x < n && y < n1; z++)
            if (left[x] <= right[y])
                array[z] = left[x++];
            else
                array[z] = right[y++];

        for (; x < n; x++, z++)
            array[z] = left[x];

        for (; y < n1; y++, z++)
            array[z] = right[y];
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

    static T* MergeSort(T* array, const size_t l, const size_t r)
    {
        if (l < r)
        {
            size_t mid = (l + (r - 1)) / 2;

            MergeSort(array, l, mid);
            MergeSort(array, mid + 1, r);

            Merge(array, l, mid, r);
        }

        return array;
    }
};

#endif // SORT_H_
