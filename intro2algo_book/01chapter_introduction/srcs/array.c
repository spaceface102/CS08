#include "array.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void printArray(int array[], uint64_t size)
{
    for (uint64_t k = 0; k < size; k++)
        printf("%d ", array[k]);
    printf("\n");
}
void randomizeArray(int array[], uint64_t size)
{
    srand(time(NULL));
    for (uint64_t k = 0; k < size; k++)
        array[k] = rand();
}

void randomizeArray_range(int array[], uint64_t size, int min, int max)
{
    if (max < min)
    {
        randomizeArray(array, size);
        return;
    }
    
    srand(time(NULL));
    for (uint64_t k = 0; k < size; k++)
        array[k] = (rand()%((max - min) + 1)) + min;
}