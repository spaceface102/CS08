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

    Bag<E>& operator=(const Bag<E>& that);
    void insert(const E& value);
    bool erase(const E& target); //remove all instances of target
    bool erase_one(const E& target); //remove the first instance of the target
    Bag<E>& operator+=(const Bag<E>&that);
    E& operator[](uint64_t index);

    uint64_t count(const E& target) const; //returns the numbers of instances of target
    uint64_t getSize(void) const; //returns the number of elements stored
    uint64_t getCapacity(void) const; //returns max size of internal array
    Bag<E> operator+(const Bag<E>& that) const;
    const E& operator[](uint64_t index) const;


private:
    void expand(void);
    void expand(uint64_t new_capacity);
    inline bool isInArray(const E& value);
    inline uint64_t inArray_RelativeOffset(const E& value);

    uint64_t size;
    uint64_t capacity;
    E* array;
};

#include "bag.cpp"

template<typename E>
std::ostream& operator<<(std::ostream& out, const Bag<E>& a_bag);

#endif //BAG_CLASS_H