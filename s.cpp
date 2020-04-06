#include <iostream>
#include <string.h>
#include <stdlib.h>

void BubbleSort(char*);
int ArrayLength(char*);

int main()
{

    return 0;
}

int ArrayLength(char* array[])
{
	int len;

	for (len = 0; strcmp(array[len], "\0") != 0; len++)	;

	return len;
}

void BubbleSort(char* array[])
{
    for (int x = 0; x < ArrayLength(array) - 1; x++)
		if (strcmp(array[x], array[x + 1]) > 0)
			Swap(array[x], array[x + 1]);

}

void Swap(char* array, char* array1)
{	
	char* temp = array;
	array = array1;
	array1 = temp;
}