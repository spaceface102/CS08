#ifndef BAG_CLASS_H
#define BAG_CLASS_H

#include <cstdint>
#include <iostream>

template<typename E>
class Bag
{
public:
    Bag(void);
    Bag(const Bag<E>& that);
    ~Bag(void);

    Bag<E>& operator = (const Bag<E>& that);
    void insert(const E& value); //adds item to the array
    bool erase(const E& target); //remove all instances of target
    bool erase_one(const E& target); //remove the first instance of the target
    Bag<E>& operator +=(const Bag<E>&that);
    Bag<E>& operator [](uint64_t index);

    void count(const E& target) const; //returns the numbers of instances of target
    void size(void) const; //returns the number of elements stored
    void capacity(void) const; //returns max size of internal array
    Bag<E> operator +(const Bag<E>&that) const;
    const Bag<E>& operator [](uint64_t index) const;

private:
    void setCapacity(uint64_t new_capacity);
    void doubleCapcity(void);
    inline bool isInArray(const E& value);
    inline uint64_t inArray_RelativeOffset(const E& value);

    uint64_t size;
    uint64_t capacity;
    E* array;
};

template<typename E>
std::ostream& operator <<(std::ostream& out, const Bag<E>& a_bag);

#include "bag.cpp"

#endif //BAG_CLASS_H