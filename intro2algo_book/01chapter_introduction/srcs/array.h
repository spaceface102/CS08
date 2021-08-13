#ifndef ARRAY_H
#define ARRAY_H

#include <stdint.h>

void printArray(int array[], uint64_t size);
void randomizeArray(int array[], uint64_t size);
void randomizeArray_range(int array[], uint64_t size, int min, int max);

#endif //ARRAY_H