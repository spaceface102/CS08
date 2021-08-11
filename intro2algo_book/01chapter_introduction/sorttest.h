#ifndef SORT_TEST_H
#define SORT_TEST_H


#include <stdint.h>
#include <stdbool.h>

//affects isSorted, testSortFunc, and
//CompareSortFuncs (indirectly from
//using testSortFunc)
#define EXTRA_INFO 0
typedef void (*sortFunc)(int array[], uint64_t size);

//FUNCTION DECLERATIONS
bool isSorted(int array[], uint64_t size);
double timeSortingFunc(sortFunc sortfunc, int array[], uint64_t size);

void testSortFunc(sortFunc sortfunc, const char* sortfuncName,
                    int array[], uint64_t size);

void CompareSortFuncs(sortFunc sortfuncArray[], 
                            const char* sortfuncNames[],
                            uint64_t numSortFuncs, 
                            uint64_t maxArraySize,
                            uint64_t multiplier);
//END OF FUNCTION DECLERATIONS

#endif //SORT_TEST_H