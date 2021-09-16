#ifndef BAG_CLASS_CPP
#define BAG_CLASS_CPP

#include "bag.h"
#include <stdexcept>

template<typename E>
Bag<E>::Bag(void) noexcept
    : size(0), capacity(0), array(nullptr)
{}
//EOF

template<typename E>
Bag<E>::Bag(const Bag<E>& that) noexcept
{
    this->size = that.size;
    this->capacity = that.capacity;
    this->array = new E[this->capacity]();

    for (uint64_t i = 0; i < that.size; i++)
        this->array[i] = that.array[i];
}
//EOF

template<typename E>
Bag<E>::~Bag(void) noexcept
{
    size = capacity = 0;
    delete [] array;
    array = nullptr;
}
//EOF

template<typename E>
Bag<E>& Bag<E>::operator=(const Bag<E>& that) noexcept
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
void Bag<E>::insert(const E& value) noexcept
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
        valueIs_IN_InternalArray = addressIsInArray(value);
        if (valueIs_IN_InternalArray)
            valueRelativeOffset_InArray = inArray_RelativeOffset(value);
        //use a relative offset to avoid copying
        doubleCapacity();
    }

    array[size++] = (valueIs_IN_InternalArray) ? array[valueRelativeOffset_InArray] : value;
}
//EOF

template<typename E>
bool Bag<E>::erase(const E& target) noexcept
{
    //there are not going to be any targets in a bag of size 0!
    if (size == 0)
        return false;

    //handle the event in which the passed in target is
    //a reference to an element in the internal array
    //and therefore would be over-written when shiting 
    //values to the left
    if (addressIsInArray(target))
    {
        E copyOfTarget = target;
        return erase(copyOfTarget);
    }

    uint64_t shift_left_amount = 0; //goes up every time the target
                                    //is encountered, and by default
                                    //no targets have been found
    uint64_t index_of_first_target = 0; //delay copying:
                                        //array[i - shift_left_amount] = array[i]
                                        //until necessary

    //find the first target
    while (index_of_first_target < size && array[index_of_first_target] != target)
        index_of_first_target++;

    //there is no target to speak of in the whole bag
    if (index_of_first_target == size)
        return false;
    else //there is definitely an instance of target in the bag and not at the end
        shift_left_amount++;

    for (uint64_t i = index_of_first_target; i < size - 1; i++)
    {
        //point to the next value that is the not equal to the target, and
        //count the amount of successive values that equal to the target
        //i < size - 1 ensures that i at max will be eq to size - 1, need this
        //since max index is size - 1 NOT size, and will be accesing index i (array[i])
        while (i < size - 2 && array[i] == target) 
            {i++; shift_left_amount++;} //notice that "i" is also being incremeneted

        array[i - shift_left_amount] = array[i];
    }

    //used to catch in the event that the last element is
    //equal to the target
    if (array[size - 1] == target)
        size -= 1;

    //remember, shift_left_amount also tells us
    //how many targets we encountered since in the
    //while loop we incremented shift_left_amount
    //every single time that array[i] == target
    //therefore we have shift_left_amount less values
    size -= shift_left_amount;

    //decreasing capacity of bag, free memory if necessary
    shrinkConditionally();

    return (bool)shift_left_amount; //if 0 then false, else true
}
//EOF

template<typename E>
bool Bag<E>::erase_one(const E& target) noexcept
{
    //there are not going to be any targets in a bag of size 0!
    if (size == 0)
        return false;

    uint64_t positionOfTarget = 0;
    for (; positionOfTarget < size && array[positionOfTarget] != target; positionOfTarget++) {}

    //went through the whole array, no instance of target
    if (positionOfTarget == size)
        return false;

    for (uint64_t i = positionOfTarget + 1; i < size; i++)
        array[i - 1] = array[i];

    size -= 1;

    //decreasing capacity of bag, free memory if necessary
    shrinkConditionally();

    return true; //indeed found the target
}
//EOF

template<typename E>
void Bag<E>::clear(void) noexcept
{
    delete [] array;
    array = nullptr;
    size = 0;
    capacity = 0;
}

template<typename E>
Bag<E>& Bag<E>::operator+=(const Bag<E>& that) noexcept
{
    if (this->size + that.size <= this->capacity)
    {
        for (uint64_t i = 0; i < that.size; i++)
            array[i + this->size] = that.array[i];
        this->size += that.size;
    }
    else //not enough capacity
    {
        this->expand(this->size + that.size);
        for (uint64_t i = 0; i < that.size; i++)
            array[i + this->size] = that.array[i];
        this->size += that.size;
    }

    return *this;
}
//EOF

template<typename E>
E& Bag<E>::operator[](uint64_t index) noexcept(false)
{
    if (index >= size)
        throw std::out_of_range("Invalid memory access!\nMake sure index < size");
    return array[index];
}
//EOF

template<typename E>
uint64_t Bag<E>::count(const E& target) const noexcept
{
    uint64_t number_of_targets = 0;
    for (uint64_t i = 0; i < size; i++)
        if (array[i] == target)
            number_of_targets++;
    return number_of_targets;
}
//EOF

template<typename E>
uint64_t Bag<E>::getSize(void) const noexcept
{
    return this->size;
}
//EOF


template<typename E>
uint64_t Bag<E>::getCapacity(void) const noexcept
{
    return this->capacity;
}
//EOF

template<typename E>
Bag<E> Bag<E>::operator+(const Bag<E>& that) const noexcept
{
    Bag<E> output;

    output.setNewCapacity(this->size + that.size);
    output.size = this->size + that.size;

    for (uint64_t i = 0; i < this->size; i++)
        output.array[i] = this->array[i];
    for (uint64_t i = 0; i < that.size; i++)
        output.array[i + this->size] = that.array[i];

    return output;
}
//EOF

template<typename E>
const E& Bag<E>::operator[](uint64_t index) const noexcept(false)
{
    if (index >= size)
        throw std::out_of_range("Invalid memory access!\nMake sure index < size");
    return array[index];
}
//EOF

template<typename E>
bool Bag<E>::isEmpty(void) const noexcept
{
    return size == 0;
}

template<typename E>
void Bag<E>::setNewCapacity(uint64_t new_capacity) noexcept
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
void Bag<E>::doubleCapacity(void) noexcept
{
    if (capacity == 0)
        setNewCapacity(1);
    else
        setNewCapacity(capacity*2);
}
//EOF

template<typename E>
void Bag<E>::expand(uint64_t suggested_new_capacity) noexcept
{
    if (suggested_new_capacity > capacity * 2)
        setNewCapacity(suggested_new_capacity);
    else
        setNewCapacity(capacity * 2);
}
//EOF

template<typename E>
inline bool Bag<E>::addressIsInArray(const E& value) noexcept
{
    //although array + capacity will also determine if inside
    //the array, array + size might be safer since only allowing
    //addresses that have already been populated
    return (&value >= array) && (&value < (array + size));
}
//EOF

template<typename E>
void Bag<E>::shrinkConditionally(void) noexcept
{
    shrinkConditionally(size * 2 < capacity, size);
}
//EOF

template<typename E>
void Bag<E>::shrinkConditionally(bool your_condition_logic, uint64_t new_capacity) noexcept
{
    if (your_condition_logic)
        setNewCapacity(new_capacity);
}
//EOF

template<typename E>
inline uint64_t Bag<E>::inArray_RelativeOffset(const E& value) noexcept
{
    return (&value) - array;
}
//EOF

template<typename E>
std::ostream& operator<<(std::ostream& out, const Bag<E>& a_bag) noexcept
{
    for (uint64_t i = 0; i < a_bag.getSize(); i++)
        out << a_bag[i] << " ";
    return out;
}
//EOF

#endif //BAG_CLASS_CPP