#ifndef MYVECTOR_CLASS_H
#define MYVECTOR_CLASS_H

#include <iostream>
#include <stdexcept>
#include <cstdint>

template<typename E>
class MyVector
{
private:
    uint64_t sz; //IN - size of vector (defines accessible elements)
    uint64_t cap;//IN - capacity of vector (defines when need to expand data)
    E* data;   //IN - where all the data is stored.

public:
    /*****************************
    ** CONSTRUCTOR & DESTRUCTOR **
    *****************************/
    MyVector(void);
    MyVector(uint64_t size);
    MyVector(uint64_t size, const E& value);
    ~MyVector(void);

    /**************
    ** ACCESSORS **
    **************/
    uint64_t size() const;
    uint64_t capacity() const;
    bool empty() const;
    const E& at(uint64_t index) const noexcept(false);
    const E& front() const noexcept(false);
    const E& back() const noexcept(false);

    /*************
    ** MUTATORS **
    *************/
    void insert(uint64_t index, const E& value) noexcept(false);
    void erase(uint64_t index) noexcept(false);
    void push_back(const E& value);
    void pop_back(void) noexcept(false);
    void clear(void);
    void resize(uint64_t size);
    void resize(uint64_t size, const E& value);
    void reserve(uint64_t n);
    void assign(uint64_t n, const E& value);
    E& at(uint64_t index) noexcept(false);
    E& front() noexcept(false);
    E& back() noexcept(false);

    //EXTRA to meet rules of 3
    MyVector(const MyVector<E>& obj);
    MyVector& operator=(const MyVector<E>& obj);

    //Added for CS08
public:
    void add(const E& value);
    E& get(unsigned index);
    const E& get(unsigned index) const;
    void resize(void);

private:
    void expand(void);
    void expand(uint64_t amount);
};

//For CSO8
typedef MyVector<int> IntVector;

#include "myVector.cpp"

#endif //MYVECTOR_CLASS_H