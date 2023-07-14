#include <iostream>
#include "Sort.h"

int main()
{
    int array[10] = {
        3, 43, 54, 23, 44, 54, 23, 22, 12, 59
    };

    int size = sizeof(array) / sizeof(int);

    Sorting<int>::MergeSort(array, 0, 9);

    for (int x = 0; x < 10; x++)
        std::cout << array[x] << ' ';

    std::cout << '\n';

    return 0;
}
