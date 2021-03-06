#include "mysort.h"
#include "sorttest.h"
#include "array.h"
#include <stdlib.h>

int main(int argc, char *argv[])
{
    sortFunc allsortFuncs[] = 
    {
        insertionSort
    };

    const char* sortfuncNames[] = 
    {
        "Insertion Sort"
    };

    uint64_t numsortFuncs = sizeof(allsortFuncs)/sizeof(sortFunc);

    CompareSortFuncs(
        allsortFuncs, sortfuncNames,
        numsortFuncs, 1e5, 10
    );

    return 0;
}