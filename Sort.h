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

enum class SortingAlgorithms
{
    QuickSort
};

class Sorting
{
public:
        template<typename T>
        static int Partition(T* array, unsigned int start, unsigned int end)
        {
            T pivot = array[end];

            int i = start - 1;

            for (int x = start; x < end; x++)
                if (array[x] <= pivot)
                {
                    i++;

                    Swap<int>(&array[i], &array[x]);
                }

            Swap<int>(&array[++i], &array[end]);

            return i;
        }

        template<typename T>
        static T* QuickSort(T* array, unsigned int start, unsigned int end)
        {
            int q;

            if (start < end)
            {
                q = Sorting::Partition<T>(array, start, end);

                QuickSort(array, start, q - 1);
                QuickSort(array, q + 1, end);
            }

            return array;
        }
};

#endif // SORT_H_
