#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

void mergeSort(int array[], uint64_t size, int depth);
void repeatChar(char c, int times);

void mergeSort(int array[], uint64_t size, int depth)
{
    if (size > 1)
    {
        const bool isOdd = size % 2;
        const uint64_t halfSize = size / 2;

        repeatChar('\t', depth);
        printf("IN left: %lu\n", size);
        mergeSort(array, halfSize + isOdd, depth+1);
        repeatChar('\t', depth);
        printf("OUT left: %lu\n", size);

        repeatChar('\t', depth);
        printf("IN right: %lu\n", size);
        mergeSort(array + halfSize + isOdd, halfSize, depth+1);
        repeatChar('\t', depth);
        printf("OUT right: %lu\n", size);

        return;
    }

    //assured to be size = 1
    repeatChar('\t', depth);
    printf("END: 1\n");
}

void repeatChar(char c, int times)
{
    for (int i = 0; i < times; i++)
        putchar(c);
}

int main(void)
{
    int array[7] = {100, 20, 15, 30, 5, 75, 40};
    mergeSort(array, sizeof(array)/sizeof(int), 0);
    return 0;
}