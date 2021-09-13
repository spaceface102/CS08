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

}
//EOF

template<typename E>
void Bag<E>::setCapacity(uint64_t new_capacity)
{
    E* temp_array = new E[new_capacity];

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
#endif