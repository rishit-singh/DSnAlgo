#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** GetInput();
void BubbleSort(char**);
void PrintArray(char**);
void Swap(char*, char*);
void ArrayCopy(char**, char**);
int ArrayLength(char**);

int main()
{
    //char** array = new char*[10];
    char** input = (char**) malloc(sizeof(char*) * 1000);

    ArrayCopy(input, GetInput());

    printf("%s", *(GetInput() + 0));

    BubbleSort(input);
    PrintArray(input); 

    return 0;
}

void ArrayCopy(char** array0, char** array1)
{
    for (int x = 0; strcmp(*(array1 + x), "\0") != 0; x++)
        strcpy(*(array0 + x), *(array1 + x));
}

int ArrayLength(char** array)
{
    int len;

    for (int len = 0; strcmp(*(array + len), "\0") != 0; len++) ;

    return len;
}

void BubbleSort(char** array) 
{   
    printf("Sort function called.");

    for (int x = 0; x < ArrayLength(array) / 2; x++)
        if (strcmp(*(array + x), *(array + (x + 1))) > 0)
            Swap(*(array + x), *(array + (x + 1)));
}

void Swap(char* val0, char* val1)
{
    char* temp = (char*) malloc(sizeof(char) * 1000);

    temp = val0;
    val0 = val1;
    val1 = val0;
    // strcpy(temp, val0);
    // strcpy(val0, val1);
    // strcpy(val1, temp);
}

char** GetInput()
{
    char** array = (char**) malloc(sizeof(char) * 1000);

    for (int x = 0; x < 3; x++)
    {
    	*(array + x) = (char*) malloc(sizeof(char) * 1000);
		scanf("%s", *(array + x));
    }

    return array;
}
    
void PrintArray(char** array)
{
    for (int x = 0; strcmp(*(array + x), "\0") != 0; x++)
        printf("%s\n", *(array + x));
}