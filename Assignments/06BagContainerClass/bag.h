#ifndef BAG_CLASS_H
#define BAG_CLASS_H

#include <cstdint>

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

    void count(const E& target) const; //returns the numbers of instances of target
    void size(void) const; //returns the number of elements stored
    void capacity(void) const; //returns max size of internal array
    Bag<E> operator +(const Bag<E>&that) const;

private:
    void setCapacity(uint64_t new_capacity);
    void doubleCapcity(void);

    uint64_t size;
    uint64_t capacity;
    E* array;
};

#include "bag.cpp"

#endif //BAG_CLASS_H