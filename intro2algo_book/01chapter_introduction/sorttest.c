#include "sorttest.h"
#include <time.h>

double timeSortingFunc(sortFunc s, int array[], uint64_t size)
{
    clock_t start = clock();
    s(array, size);
    return ((double)(clock() - start))/CLOCKS_PER_SEC;
}