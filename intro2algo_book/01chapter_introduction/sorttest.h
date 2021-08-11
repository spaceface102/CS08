#ifndef SORT_TEST_H
#define SORT_TEST_H

#include <stdint.h>

typedef void (*sortFunc)(int array[], uint64_t size);
double timeSortingFunc(sortFunc s, int array[], uint64_t size);

#endif //SORT_TEST_H