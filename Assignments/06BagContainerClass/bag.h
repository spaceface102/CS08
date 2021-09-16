#ifndef BAG_CLASS_H
#define BAG_CLASS_H

#include <cstdint>
#include <iostream>
template<typename E>
class Bag
{
public:
    Bag(void) noexcept;
    Bag(const Bag<E>& that) noexcept;
    ~Bag(void) noexcept;

    Bag<E>& operator=(const Bag<E>& that) noexcept;
    void insert(const E& value) noexcept; //add a given object to the bag
    bool erase(const E& target) noexcept; //remove all instances of target
    bool erase_one(const E& target) noexcept; //remove the first instance of the target
    void clear(void) noexcept;
    Bag<E>& operator+=(const Bag<E>&that) noexcept;
    E& operator[](uint64_t index) noexcept(false);

    uint64_t count(const E& target) const noexcept; //returns the numbers of instances of target
    uint64_t getSize(void) const noexcept; //returns the number of elements stored
    uint64_t getCapacity(void) const noexcept; //returns max size of internal array
    Bag<E> operator+(const Bag<E>& that) const noexcept;
    const E& operator[](uint64_t index) const noexcept(false);
    bool isEmpty(void) const noexcept;

private:
    void setNewCapacity(uint64_t new_capacity) noexcept;
    void doubleCapacity(void) noexcept;
    void expand(uint64_t suggested_new_capacity) noexcept;
    void shrinkConditionally(void) noexcept;
    void shrinkConditionally(bool your_condition_logic, uint64_t new_capacity) noexcept;
    inline bool addressIsInArray(const E& value) noexcept;
    inline uint64_t inArray_RelativeOffset(const E& value) noexcept;

    uint64_t size;
    uint64_t capacity;
    E* array;
};

#include "bag.cpp"

template<typename E>
std::ostream& operator<<(std::ostream& out, const Bag<E>& a_bag) noexcept;

#endif //BAG_CLASS_H