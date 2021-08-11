#include "insertion_sort.h"

void insertionSort(int array[], uint64_t size)
{
    int key;
    uint64_t subIndex;
    uint64_t mainIndex;

    mainIndex = 1;
    for (; mainIndex < size; mainIndex++)
    {
        //have to store value of array[mainIndex] into a key
        //since when shifting the array to the right, will
        //overwrite the original value of value at array[mainIndex]
        key = array[mainIndex];

        subIndex = mainIndex - 1; //subIndex maximum value size size - 2

        //in the event that the key is already sorted, then the
        //condition array[subIndex] > key is automatically false
        //and nothing is done. Note, mainIndex = subIndex + 1, and
        //since key = array[mainIndex], setting array[subIndex + 1]
        //to key, has no effect whats so ever.

        //In the event that the key is NOT already sorted, subIndex
        //will traverse through the array "pointing" to possible
        //valid index to insert the key at. What we are doing in
        //this loop is just shifting all the indicies that contain
        //a value greater than the key to the right, in order
        //to make room for the correct position 
        for (; subIndex >= 0 && array[subIndex] > key; subIndex--)
            array[subIndex + 1] = array[subIndex];
        array[subIndex + 1] = key;
    }
}