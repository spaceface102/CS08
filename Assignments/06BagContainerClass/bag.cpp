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
    if (size == 0)
        return false;

    if (addressIsInArray(target))
    {
        //target is a reference to an instance of E, if the
        //reference is internal (it a reference to an element
        //in the bag) then make a copy to make sure not to modify
        //target accidentally with array[i] modifications
        E copyOfTarget = target;
        return erase(copyOfTarget);
    }

    uint64_t number_of_targets = 0;
    uint64_t index_of_first_target = 0;

    //find the first target's index
    while (index_of_first_target < size && array[index_of_first_target] != target)
        index_of_first_target++;

    //no target to speak of, do nothing and report target as not being in bag
    if (index_of_first_target == size)
        return false;
    else
        number_of_targets++;

    //takes care of successive targets at the END of the bag
    //by decreasing the "size" var to virtually cut off access
    //don't need to increment number_of_targets since in
    //essence after the end of this loop, the bag will not
    //even be able to access those targets due to size--
    for (
        uint64_t i = size - 1;
        i > index_of_first_target && array[i] == target;
        i--, size--
    )
        {}

    //start looking at the indicies right after the first
    //target and shift the array to the left
    for (uint64_t i = index_of_first_target + 1; i < size; i++)
    {
        //note that even though there is a nested loop
        //the loop itself is incrementing the same "i";
        //this is still linear!!!
        while (i < size - 1 && array[i] == target) 
            {i++; number_of_targets++;}

        array[i - number_of_targets] = array[i];
    }

    size -= number_of_targets;
    shrinkConditionally();

    return true; //there were targets in the bag
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
    size = 0;
}

template<typename E>
void Bag<E>::full_clear(void) noexcept
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