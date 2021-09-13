#include "merge_sort.h"
#include <stdbool.h>

void mergeSort(int array[], uint64_t size)
{
    if (size > 1)
    {
        const bool isOdd = size % 2;
        const uint64_t halfSize = size / 2;
        mergeSort(array, halfSize + isOdd);
        mergeSort(array + halfSize + isOdd, halfSize);
    }
    //size must be == 1
}