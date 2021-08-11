#include "sorttest.h"
#include "array.h"
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

bool isSorted(int array[], uint64_t size)
{
    for (uint64_t k = 1; k < size; k++)
        if (array[k - 1] > array[k])
        {
            printf("Failed isSorted() Dump:\n"
                "\tSize of array: %lu\n"
                "\tFailed index (counting from 0): %lu\n"
                "\tarray[index] = %d\n"
                "\tarray[index - 1] = %d\n",
                size, k, array[k], array[k - 1]
            );
            return false;
        }

    return true;
}

double timeSortingFunc(sortFunc sortfunc, int array[], uint64_t size)
{
    clock_t start = clock();
    sortfunc(array, size);
    return ((double)(clock() - start))/CLOCKS_PER_SEC;
}

void testSortFunc(sortFunc sortfunc, const char* sortfuncName,
                int array[], uint64_t size)
{
    printf("SORT FUNCTION: %s\n", sortfuncName);
    printf("ARRAY SIZE   : %lu\n", size);

    #if EXTRA_INFO
    printf("\nUnsorted array:\n");
    printArray(array, size);
    printf("\n");
    #endif

    printf("Time took: %lfs\n", timeSortingFunc(sortfunc, array, size));

    printf("%s\n", (isSorted(array, size)) ? 
        "Sorted successfully!" :
        "ERROR, not sorted correctly!"
    );


    #if EXTRA_INFO
    printf("\nSorted array:\n");
    printArray(array, size);
    printf("\n");
    #endif
}

void CompareSortFuncs(sortFunc sortfuncArray[], 
                            const char* sortfuncNames[],
                            uint64_t numSortFuncs, 
                            uint64_t maxArraySize,
                            uint64_t multiplier)
{
    int *baseRandArray = NULL;
    int *currentRandArray = NULL;
    uint64_t currentArraySize;
    uint64_t prevArraySize;
    uint64_t numBytes;

    if (multiplier < 2)
        multiplier = 2;
    
    prevArraySize = 0;
    currentArraySize = 1;
    for (; currentArraySize <= maxArraySize; currentArraySize *= multiplier)
    {
        numBytes = currentArraySize*sizeof(int);
        baseRandArray = (int *)realloc(baseRandArray, numBytes);
        currentRandArray = (int *)malloc(numBytes);

        //just add on to the new part of the initalized array,
        //no need to do the whole array again.
        //this also ensures that the time taken for a larger
        //array can be more easily correlated with the past array
        randomizeArray(
            baseRandArray + prevArraySize, 
            currentArraySize - prevArraySize
        );
        for (uint64_t k = 0; k < numSortFuncs; k++)
        {
            //make sure every sort function has the same random
            //array to sort
            memcpy(currentRandArray, baseRandArray, numBytes);
            testSortFunc(sortfuncArray[k], sortfuncNames[k], 
                currentRandArray, currentArraySize
            );
            printf("\n");
        }

        prevArraySize = currentArraySize;
        free(currentRandArray);
    }

    free(baseRandArray);
}
