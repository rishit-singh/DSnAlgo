#include <iostream>
#include "Sort.h"

int main()
{
    int size;

    int array[10] = {
        3, 43, 54, 23, 44, 54, 23, 22, 12, 59
    };

    size = sizeof(array) / sizeof(int);

    int* sorted = Sorting::QuickSort<int>(array, 0, size - 1);

    for (int x = 0; x < size; x++)
        std::cout << sorted[x] << ' ';

    std::cout << std::endl;

    return 0;
}
