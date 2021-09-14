#ifndef BAG_CLASS_IMPLEMENTATION
#define BAG_CLASS_IMPLEMENTATION

#include "bag.h"

template<typename E>
Bag<E>::Bag(void)
    : size(0), capacity(0), array(nullptr)
{}
//EOF

template<typename E>
Bag<E>::Bag(const Bag<E>& that)
{
    this->size = that.size;
    this->capacity = that.capacity
    this->array = new E[this->capacity]();

    for (uint64_t i = 0; i < that.size; i++)
        this->array[i] = that.array[i];
}
//EOF

template<typename E>
Bag<E>::~Bag(void)
{
    size = capacity = 0;
    delete [] array;
}
//EOF

template<typename E>
Bag<E>& Bag<E>::operator =(const Bag<E>& that)
{
    if (this == &that)
        return *this;

    if (this->capacity >= that.size)
    {
        this->size = that.size;
        //capacity stays the same, no need to increase
        for (uint64_t i = 0; i < that.size; i++)
            this->array[i] = that.array[i];
    }
    else //not enough capacity
    {
        delete [] this->array;
        this->capacity = that.capacity;
        this->size = that.size;
        this->array = new E[this->capacity];

        for (uint64_t i = 0; i < that.size; i++)
            this->array[i] = that.array[i];
    }

    return *this;
}
//EOF

//adds item to the array
template<typename E>
void Bag<E>::insert(const E& value)
{
    uint64_t valueRelativeOffset_InArray;
    bool valueIs_IN_InternalArray = false;  //default assuming "value"
                                            //is not in private "array"

    if (size == capacity)
    {
        //only have to check for valueIs_IN_InternalArray if resize occurs
        //since when capcity is increase a whole new block of memory
        //is allocated and the address of "value" is no longer valid
        //since the old block is deleted
        valueIs_IN_InternalArray = isInArray(value);
        if (valueIs_IN_InternalArray)
            valueRelativeOffset_InArray = inArray_RelativeOffset(value);
        //use a relative offset to avoid copying
        doubleCapcity();
    }

    array[size++] = (valueIs_IN_InternalArray) ? array[valueRelativeOffset_InArray] : value;
}
//EOF

template<typename E>
bool Bag<E>::erase(const E& target)
{
    uint64_t shift_left_amount = 0; //goes up every time the target
                                    //is encountered, and by default
                                    //no targets have been found
    
    for (uint64_t i = 0; i < size; i++)
    {
        //point to the next value that is the not equal to the target, and
        //count the amount of successive values that equal to the target
        while (i < size && array[i] == target) 
            {i++; shift_left_amount++;} //notice that "i" is also being incremeneted
        //does the actual shifting
        array[i - shift_left_amount] = array[i];
    }

    //remember, shift_left_amount also tells us
    //how many targets we encountered since in the
    //while loop we incremented shift_left_amount
    //every single time that array[i] == target
    //therefore we have shift_left_amount less values
    this->size -= shift_left_amount;

    return shift_left_amount; //if 0 then false, else true
}
//EOF

template<typename E>
bool Bag<E>::erase_one(const E& target)
{
    uint64_t positionOfTarget = 0;
    for (; positionOfTarget < size && array[positionOfTarget] != target; positionOfTarget++) {}

    if (positionOfTarget == size) //went through the whole array, no instance of target
        return false;
    
    for (int i = positionOfTarget + 1; i < size; i++)
        array[i - 1] = array[i];

    size -= 1;
    return true;
}

template<typename E>
void Bag<E>::setCapacity(uint64_t new_capacity)
{
    E* temp_array = new E[new_capacity]();

    capacity = new_capacity;
    for (uint64_t i = 0; i < size; i++)
        temp_array[i] = array[i];

    delete [] array;
    array = temp_array;
}
//EOF

template<typename E>
void Bag<E>::doubleCapcity(void)
{
    if (capacity == 0)
        setCapacity(1);
    else
        setCapacity(capacity*2);
}
//EOF

template<typename E>
inline bool Bag<E>::isInArray(const E& value)
{
    //although array + capacity will also determine if inside
    //the array, array + size might be safer since only allowing
    //addresses that have already been populated
    return (&value >= array) && (&value < (array + size));
}

template<typename E>
inline uint64_t Bag<E>::inArray_RelativeOffset(const E& value)
{
    return (&value) - array;
}

template<typename E>
std::ostream& operator <<(std::ostream& out, const Bag<E>& a_bag)
{
    for (int i = 0; i < a_bag.size(); i++)
        out << a_bag[i];
    return out;
}

#endif //BAG_CLASS_IMPLEMENTATION