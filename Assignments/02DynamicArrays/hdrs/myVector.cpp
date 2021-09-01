#ifndef MYVECTOR_CLASS_IMPLENTATION
#define MYVECTOR_CLASS_IMPLENTATION

#include "myVector.h"
/****************************************************************
 * 
 *  Method Constructor: Class MyVector
 *  //DEFAULT CONSTRUCTOR
 * --------------------------------------------------------------
 * Sets size and capacity to 0. data is set to nullptr
 * --------------------------------------------------------------
 *  PRE-CONDITIONS
 *      Must make an object, or call the constructor with no
 *      arguments.
 * 
 *  POST-CONDITIONS
 *      The object does not have any space to store anything
 *      yet
****************************************************************/
template<typename E>
MyVector<E>::MyVector()
{
    sz = 0;
    cap = 0;
    data = nullptr;
}
//EOF

/****************************************************************
 * 
 *  Method Constructor: Class MyVector
 *  //CONSTRUCTOR
 * --------------------------------------------------------------
 * Takes uint64_t size arg and sets it to both capacity and size.
 * allocate array of E equivalent to size, and set it to all the
 * default values of the templated type.
 * --------------------------------------------------------------
 *  PRE-CONDITIONS
 *      Must make an object, or call the constructor with no
 *      arguments.
 * 
 *  POST-CONDITIONS
 *      The object's sz = size as well as cap = size.
****************************************************************/
template<typename E>
MyVector<E>::MyVector(uint64_t size)
{
    sz = size;
    cap = size;
    data = new E[cap]();
}
//EOF

/****************************************************************
 * 
 *  Method Constructor: Class MyVector
 *  //CONSTRUCTOR
 * --------------------------------------------------------------
 * Takes uint64_t size arg and sets it to both capacity and size.
 * allocate array of E equivalent to size. All the array indices
 * are then set to the const E& value passed E.
 * --------------------------------------------------------------
 *  PRE-CONDITIONS
 *      Must make an object, or call the constructor with no
 *      arguments.
 * 
 *  POST-CONDITIONS
 *      The object's sz = size as well as cap = size. All the
 *      values in the private data attribute are set to value.
****************************************************************/
template<typename E>
MyVector<E>::MyVector(uint64_t size, const E& value)
{
    sz = size;
    cap = size;
    data = new E[cap];
    for (uint64_t i = 0; i < size; i++)
        data[i] = value;
}
//EOF

/****************************************************************
 * 
 *  Method Destructor: Class MyVector
 *  //DESTRUCTOR
 * --------------------------------------------------------------
 * Frees all the dynamically allocated memory associated with
 * the class.
 * --------------------------------------------------------------
 *  PRE-CONDITIONS
 *      Object must get out of scope or must use the delete
 *      operator on a pointer to a MyVector object.
 * 
 *  POST-CONDITIONS
 *      The pointer to the private data attribute is set to
 *      nullptr after done with the destructor.
****************************************************************/
template<typename E>
MyVector<E>::~MyVector()
{
    delete [] data;
    data = nullptr;
}

/****************************************************************
 * 
 *  Method size: Class MyVector
 *  //PUBLIC
 * --------------------------------------------------------------
 *  Returns the size of the object, aka all the indices filled
 *  with data.
 * --------------------------------------------------------------
 *  PRE-CONDITIONS
 *      Must call method on an object; not a static method.
 * 
 *  POST-CONDITIONS
 *      The object's state will not be modified whatsoever.
****************************************************************/
template<typename E>
uint64_t MyVector<E>::size() const
{
    return sz;
}
//EOF

/****************************************************************
 * 
 *  Method capacity: Class MyVector
 *  //PUBLIC
 * --------------------------------------------------------------
 *  Returns the capacity of the object, aka the amount of
 *  memory allocated.
 * --------------------------------------------------------------
 *  PRE-CONDITIONS
 *      Must call method on an object; not a static method.
 * 
 *  POST-CONDITIONS
 *      The object's state will not be modified whatsoever.
****************************************************************/
template<typename E>
uint64_t MyVector<E>::capacity() const
{
    return cap;
}
//EOF

/****************************************************************
 * 
 *  Method empty: Class MyVector
 *  //PUBLIC
 * --------------------------------------------------------------
 *  Returns a boolean defining if the vector is empty
 *  (private attribute sz).
 * --------------------------------------------------------------
 *  PRE-CONDITIONS
 *      Must call method on an object; not a static method.
 * 
 *  POST-CONDITIONS
 *      The object's state will not be modified whatsoever.
****************************************************************/
template<typename E>
bool MyVector<E>::empty() const
{
    return sz == 0;
}
//EOF

/****************************************************************
 * 
 *  Method at: Class MyVector
 *  //PUBLIC
 * --------------------------------------------------------------
 *  Returns a const reference to the data associated with the
 *  index passed in. If the index is greater than or equal to 
 *  size, the method will throw an exception std::out_of_range.
 * --------------------------------------------------------------
 *  PRE-CONDITIONS
 *      Must call method on an object; not a static method.
 *      Index should be less than or equal to private attribute sz
 * 
 *  POST-CONDITIONS
 *      The object's state will not be modified whatsoever if
 *      the index is passed in within the bounds.
 *      Else, the memory allocated (if memory is allocated)
 *      is freed and the program exits.
****************************************************************/
template<typename E>
const E& MyVector<E>::at(uint64_t index) const noexcept(false)
{
    if (index >= sz)
        throw std::out_of_range(
        "Method: const E& MyVector<E>::at(uint64_t index)\n"
        "Invalid index! uint64_t index\n"
        );

    return data[index];
}
//EOF

/****************************************************************
 * 
 *  Method at: Class MyVector
 *  //PUBLIC
 * --------------------------------------------------------------
 *  Returns a reference to the data associated with the
 *  index passed in. If the index is greater than or equal to 
 *  size, the method will throw an exception std::out_of_range.
 * --------------------------------------------------------------
 *  PRE-CONDITIONS
 *      Must call method on an object; not a static method.
 *      Index should be less than or equal to private attribute sz
 * 
 *  POST-CONDITIONS
 *      The returned refernce, if modified, will see the
 *      modification seen in the object, since it now using
 *      a reference without a const qualifer. Therefore can
 *      use the assignment operator on the resulting return value.
****************************************************************/
template<typename E>
E& MyVector<E>::at(uint64_t index) noexcept(false)
{
    if (index >= sz)
        throw std::out_of_range(
        "Method: E& MyVector<E>::at(uint64_t index)\n"
        "Invalid index! uint64_t index\n"
        );

    return data[index];
}
//EOF

/****************************************************************
 * 
 *  Method front: Class MyVector
 *  //PUBLIC
 * --------------------------------------------------------------
 *  Returns a const reference of the const E& value at the very front
 *  of the VectorInt object. Equivalent to obj.at(0). Will throw
 *  std::out_of_range exception in the even trying to be used
 *  on a vector of size 0.
 * --------------------------------------------------------------
 *  PRE-CONDITIONS
 *      The object's capacity must be > 0! If not, you
 *      will access memory you are not supposed to. Size
 *      should also be greater than 0, and you will most
 *      likely get garbage values if size = 0, but it is 
 *      especially dangerous if capacity = 0.
 * 
 *  POST-CONDITIONS
 *      The state of the object will remain the same. No
 *      modification to any of the private attributes.
****************************************************************/
template<typename E>
const E& MyVector<E>::front(void) const noexcept(false)
{
    if (sz == 0)
        throw std::out_of_range(
            "Method: const E& MyVector<E>::front(void)"
            "Size = 0! No \"front\" element!\n"
        );

    return data[0];
}
//EOF

/****************************************************************
 * 
 *  Method front: Class MyVector
 *  //PUBLIC
 * --------------------------------------------------------------
 *  Returns a reference of the const E& value at the very front
 *  of the VectorInt object. Equivalent to obj.at(0).
 *  Since a reference is returned, you are also allowed to use
 *  the assignment operator to change the value of the of the
 *  front index in the object.
 *  Will throw
 *  std::out_of_range exception in the even trying to be used
 *  on a vector of size 0.
 * --------------------------------------------------------------
 *  PRE-CONDITIONS
 *      The object's capacity must be > 0! If not, you
 *      will access memory you are not supposed to. Size
 *      should also be greater than 0, and you will most
 *      likely get garbage values if size = 0, but it is 
 *      especially dangerous if capacity = 0.
 * 
 *  POST-CONDITIONS
 *      The object's state comming out of the method is not
 *      modified, yet, can be modified if afterwords the 
 *      assignment operator is used on the return of the method.
****************************************************************/
template<typename E>
E& MyVector<E>::front(void) noexcept(false)
{
    if (sz == 0)
        throw std::out_of_range(
            "Method: E& MyVector<E>::front(void)"
            "Size = 0! No \"front\" element!\n"
        );

    return data[0];
}
//EOF

/****************************************************************
 * 
 *  Method back: Class MyVector
 *  //PUBLIC
 * --------------------------------------------------------------
 *  Returns a const reference of the const E& value at the very back
 *  of the VectorInt object. Equivalent to obj.at(obj.size()-1).
 *  Will throw
 *  std::out_of_range exception in the even trying to be used
 *  on a vector of size 0.
 * --------------------------------------------------------------
 *  PRE-CONDITIONS
 *      The object's capacity must be > 0! If not, you
 *      will access memory you are not supposed to. Size
 *      should also be greater than 0, and you will most
 *      likely get garbage values if size = 0, but it is 
 *      especially dangerous if capacity = 0.
 * 
 *  POST-CONDITIONS
 *      The state of the object will remain the same. No
 *      modification to any of the private attributes.
****************************************************************/
template<typename E>
const E& MyVector<E>::back(void) const noexcept(false)
{
    if (sz == 0)
        throw std::out_of_range(
            "Method: const E& MyVector<E>::back(void)"
            "Size = 0! No \"back\" element!\n"
        );

    return data[sz - 1];
}
//EOF

/****************************************************************
 * 
 *  Method back: Class MyVector
 *  //PUBLIC
 * --------------------------------------------------------------
 *  Returns a reference of the const E& value at the very back
 *  of the VectorInt object. Equivalent to obj.at(obj.size()-1).
 *  Since a reference is returned, you are also allowed to use
 *  the assignment operator to change the value of the of the
 *  back index in the object.
 *  Will throw
 *  std::out_of_range exception in the even trying to be used
 *  on a vector of size 0.
 * --------------------------------------------------------------
 *  PRE-CONDITIONS
 *      The object's capacity must be > 0! If not, you
 *      will access memory you are not supposed to. Size
 *      should also be greater than 0, and you will most
 *      likely get garbage values if size = 0, but it is 
 *      especially dangerous if capacity = 0.
 * 
 *  POST-CONDITIONS
 *      The object's state comming out of the method is not
 *      modified, yet, can be modified if afterwords the 
 *      assignment operator is used on the return of the method.
****************************************************************/
template<typename E>
E& MyVector<E>::back(void) noexcept(false)
{
    if (sz == 0)
        throw std::out_of_range(
            "Method: E& MyVector<E>::back(void)"
            "Size = 0! No \"back\" element!\n"
        );

    return data[sz - 1];
}
//EOF

/****************************************************************
 * 
 *  Method expand: Class MyVector
 *  //PRIVATE
 * --------------------------------------------------------------
 *  Double the capacity of the data array.
 * --------------------------------------------------------------
 *  PRE-CONDITIONS
 *      There must be enough memory to hold both the new bigger
 *      array, and the smaller current array, while copying is
 *      being done.
 * 
 *  POST-CONDITIONS
 *      Assuming there was enough memory, the size of the object
 *      will stay the same but the value of capacity will be
 *      doubled, and the private data array can now hold twice
 *      as many elements (and all the previous elements are also
 *      kept).
 *      Note: if cap = 0, then the new capacity will be set to 1.
****************************************************************/
template<typename E>
void MyVector<E>::expand(void)
{
    if (cap == 0)   //ensure a new object also gets memory!
        expand(1);
    else
        expand(cap);    //double capacity
}
//EOF

/****************************************************************
 * 
 *  Method expand: Class MyVector
 *  //PRIVATE
 * --------------------------------------------------------------
 *  Increase the size of the data array by the passed in arg
 *  uint64_t amount.
 * --------------------------------------------------------------
 *  PRE-CONDITIONS
 *      There must be enough memory to hold both the new bigger
 *      array, and the smaller current array, while copying is
 *      being done.
 * 
 *  POST-CONDITIONS
 *      Assuming there was enough memory, the size of the object
 *      will stay the same but the value of capacity will grow to
 *      capacity + amount, and the private data array can now "amount"
 *      more elements (and all the previous elements are also
 *      kept).
****************************************************************/
template<typename E>
void MyVector<E>::expand(uint64_t amount)
{
    E* temp;  //PROC - store the address of the new array

    cap += amount;  //change size of capacity
    temp = new E[cap];
    //copy all of contents of data to temp
    for (uint64_t i = 0; i < sz; i++)
        temp[i] = data[i];

    delete [] data; //free the previous memory
    data = temp;    //set new address for data
}
//EOF

/****************************************************************
 * 
 *  Method insert: Class MyVector
 *  //PUBLIC
 * --------------------------------------------------------------
 *  Inserts const E& value into the passed index (if index is less
 *  than the size of the MyVector object).
 * --------------------------------------------------------------
 *  PRE-CONDITIONS
 *      The MyVector object's size should be greater than 0.
 * 
 *  POST-CONDITIONS
 *      The size of the object increases by one. If the new
 *      size is larger than the capacity, will automatically
 *      set double the capacity. The closer to the front
 *      of the vector the index is, the longer the method
 *      will take, since private data structure is just an array,
 *      have to a lot of shifiting of elements.
 * 
 *      Note: if the index is invalid, clean up of the calling
 *      object is done, and the complete program ends (exit(1))
****************************************************************/
template<typename E>
void MyVector<E>::insert(uint64_t index, const E& value) noexcept(false)
{
    int64_t relativeOffset; //PROC - used for when value inside vector

    if (index >= sz) //ensure index is valid
        throw std::out_of_range(
            "Method void MyVector<E>::insert(uint64_t index, const E& value)\n"
            "Can't insert value in a invalid index!\n"
        );
    
    relativeOffset = -1;
    if (sz + 1 > cap)
    {
        //deal with value being a reference to memory
        //that will get deleted during expansion since
        //value is in the vector.
        if (data <= &value && &value < data + sz)
            relativeOffset = &value - data;

        expand();
    }
    
    for (int64_t i = sz - 1; i >= index; i--)
        data[i+1] = data[i];

    //insert value here
    data[index] = (relativeOffset != -1) ? (data[relativeOffset]) : value;
    sz += 1; //increase size
}
//EOF

/****************************************************************
 * 
 *  Method erase: Class MyVector
 *  //PUBLIC
 * --------------------------------------------------------------
 *  If the index is less than the object's size, then the value
 *  at said index is erased, and all the elements to the right
 *  of it are shifted one index down (to the left).
 * --------------------------------------------------------------
 *  PRE-CONDITIONS
 *      The MyVector object's size should be greater than 0.
 * 
 *  POST-CONDITIONS
 *      The size of the object is decrease by 1. The capacity 
 *      of the object does not change what's so ever.
 *      The closer the index is to the front of the MyVector, 
 *      the longer the method will take as more elements need
 *      to be shifted left.
 *      Note: if the index is invalid, clean up of the calling
 *      object is done, and the complete program ends (exit(1))
****************************************************************/
template<typename E>
void MyVector<E>::erase(uint64_t index) noexcept(false)
{
    if (index >= sz) //ensure index is valid
        throw std::out_of_range(
            "Method void MyVector<E>::erase(uint64_t index)\n"
            "Can't erase a value in a invalid index!\n"
        );

    //sz - 1 to not access memory were are not supposed to (data[i+1])
    for (uint64_t i = index; i < (sz - 1); i++)
        data[i] = data[i+1];

    sz -= 1;    //since we removed an index
}
//EOF

/****************************************************************
 * 
 *  Method push_back: Class MyVector
 *  //PUBLIC
 * --------------------------------------------------------------
 *  The size of the object is increase by one, and the const E& value
 *  is set to the new back of the MyVector object.
 * --------------------------------------------------------------
 *  PRE-CONDITIONS
 *      The MyVector object can be of any size and capcity,
 *      including 0.
 * 
 *  POST-CONDITIONS
 *      If the new size is greater than capacity, capacity is
 *      doubled.
****************************************************************/
template<typename E>
void MyVector<E>::push_back(const E& value)
{
    int64_t relativeOffset; //PROC - used for when value inside vector

    relativeOffset = -1; //base value, "non activated" state
    if (sz + 1 > cap)
    {
        //deal with value being a reference to memory
        //that will get deleted during expansion since
        //value is in the vector.
        if (data <= &value && &value < data + sz)
            relativeOffset = &value - data;

        expand();
    }

    sz += 1;
    data[sz - 1] = (relativeOffset != -1) ? (data[relativeOffset]) : value;
}
//EOF

/****************************************************************
 * 
 *  Method pop_back: Class MyVector
 *  //PUBLIC
 * --------------------------------------------------------------
 *  The size of the object is decreased by one. Previous back
 *  index is no longer accessible. New back index.
 * --------------------------------------------------------------
 *  PRE-CONDITIONS
 *      The object's size must be a minimum 1.
 * 
 *  POST-CONDITIONS
 *      If object's size is 0, the object's heap allocated
 *      memory is cleaned up and the whole program exists.
****************************************************************/
template<typename E>
void MyVector<E>::pop_back(void) noexcept(false)
{
    //nothing to pop!
    if (sz == 0)
        throw std::out_of_range(
            "Method void MyVector<E>::pop_back(void)\n"
            "Nothing to pop!, Size of vector = 0!\n"
        );

    sz -= 1;
}
//EOF

/****************************************************************
 * 
 *  Method clear: Class MyVector
 *  //PUBLIC
 * --------------------------------------------------------------
 *  The size of the object is set to 0.
 * --------------------------------------------------------------
 *  PRE-CONDITIONS
 *      The object can be of any size or capacity.
 * 
 *  POST-CONDITIONS
 *      The size will be set to 0, but the capacity is left
 *      untouched.
****************************************************************/
template<typename E>
void MyVector<E>::clear(void)
{
    //makes it so user can no longer access the values through
    //the public interface! capacity is untouched.
    sz = 0;
}
//EOF

/****************************************************************
 * 
 *  Method resize: Class MyVector
 *  //PUBLIC
 * --------------------------------------------------------------
 *  If the passed in size is larger than the current object's
 *  size, then more memory is accommodated if needed, and all
 *  the new unfilled indicies are filled with zeros. If passed
 *  in size is smaller than current size, then the object's
 *  size variable will simply be set to the passed in size.
 * --------------------------------------------------------------
 *  PRE-CONDITIONS
 *      The object can be of any size or capacity.
 * 
 *  POST-CONDITIONS
 *      The capacity of the MyVector is not assured to change.
 *      The only times it will change is if the passed in size
 *      is greater than capacity (note, capacity does not 
 *      necessarily need to equal to size, it's usually bigger!)
 *      If the passed in size is smaller, none of the data values
 *      are changed, but the user looses access to them through
 *      the public interface.
****************************************************************/
template<typename E>
void MyVector<E>::resize(uint64_t size)
{
    resize(size, E());
}
//EOF

/****************************************************************
 * 
 *  Method resize: Class MyVector
 *  //PUBLIC
 * --------------------------------------------------------------
 *  If the passed in size is larger than the current object's
 *  size, then more memory is accommodated if needed, and all
 *  the new unfilled indicies are filled with "value" arg. If passed
 *  in size is smaller than current size, then the object's
 *  size variable will simply be set to the passed in size.
 * --------------------------------------------------------------
 *  PRE-CONDITIONS
 *      The object can be of any size or capacity.
 * 
 *  POST-CONDITIONS
 *      The capacity of the MyVector is not assured to change.
 *      The only times it will change is if the passed in size
 *      is greater than capacity (note, capacity does not 
 *      necessarily need to equal to size, it's usually bigger!)
 *      If the passed in size is smaller, none of the data values
 *      are changed, but the user looses access to them through
 *      the public interface.
****************************************************************/
template<typename E>
void MyVector<E>::resize(uint64_t size, const E& value)
{
    int64_t relativeOffset; //PROC - used for when value inside vector

    if (size <= sz)
    {
        sz = size; //either stays the same, or it reduces in value
        return;
    }

    //then size must be greater than sz
    relativeOffset = -1; //base value, "non activated" state
    if (size > cap) //expanding capacity to meet size demands
    {
        //deal with value being a reference to memory
        //that will get deleted during expansion since
        //value is in the vector.
        if (data <= &value && &value < data + sz)
            relativeOffset = &value - data;

        (cap*2 >= size) ? expand() : expand(size - cap);
    }

    if (relativeOffset != -1)
        for (uint64_t i = sz; i < size; i++)
            data[i] = data[relativeOffset];
    else //value was not originally in the vector
        for (uint64_t i = sz; i < size; i++)
            data[i] = value;

    sz = size;  //update finnally the size
}
//EOF

/****************************************************************
 * 
 *  Method reserve: Class MyVector
 *  //PUBLIC
 * --------------------------------------------------------------
 *  The capacity of the MyVector is changed based on the passed in
 *  uint64_t "n" argument. All the previous elements held in the
 *  vector are left intact.
 * --------------------------------------------------------------
 *  PRE-CONDITIONS
 *      The object can be of any size or capacity.
 * 
 *  POST-CONDITIONS
 *      The MyVector object will never decrease in capacity.
 *      If the passed in "n" is smaller than capacity, nothing
 *      is done. The capacity is always assured to be at least
 *      the passed in "n", but may be bigger.
****************************************************************/
template<typename E>
void MyVector<E>::reserve(uint64_t n)
{
    if (cap >= n)
        return; //don't do anything, capacity is all good
    
    //assured that n > cap
    (cap*2 >= n) ? expand() : expand(n - cap);
}
//EOF

/****************************************************************
 * 
 *  Method reserve: Class MyVector
 *  //PUBLIC
 * --------------------------------------------------------------
 *  It assigns a new size to the MyVector object, and fills
 *  up that new size with the new passed in "value". The final
 *  size is set to "n". It acts to fill the whole vector of now
 *  size n, with the passed in value.
 * --------------------------------------------------------------
 *  PRE-CONDITIONS
 *      The passed in MyVector object can be of any size.
 *  POST-CONDITIONS
 *      If the new size is greater than the capacity, capacity
 *      is automatically resized to meet the needs of the new
 *      size. The values of size is always changed (unless the
 *      passed in size "n" is the same).
****************************************************************/
template<typename E>
void MyVector<E>::assign(uint64_t n, const E& value)
{
    if (n > sz)
    {
        for (uint64_t i = 0; i < sz; i++)
            data[i] = value;
        //resize() makes it so sz = n, data and capacity
        //are made bigger accordingly, and the new empty indicies
        //between sz and n (since n is larger) are filled with
        //"value"
        //NOTE: have to call after the above for loop to avoid
        //changing sz to n early, and risking a seg fault.
        resize(n, value);
    }
    else //n must be less than or equal to sz
    {   
        //this seperation of when n > sz and when n <= sz 
        //also allows for the possibility of reducing the 
        //number of value changes that need to be done on data
        //since n might be smaller than sz
        sz = n;
        for (uint64_t i = 0; i < sz; i++)
            data[i] = value;
    }

}
//EOF


//EXTRA to meet rules of 3


/****************************************************************
 * 
 *  Method Constructor: Class MyVector
 *  //COPY CONSTRUCTOR
 * --------------------------------------------------------------
 *  Used when the argument to the constructor is another
 *  MyVector object, in which case a deep copy is done.
 * --------------------------------------------------------------
 *  PRE-CONDITIONS
 *      Will only apply when making a new object.
 * 
 *  POST-CONDITIONS
 *      New memory will be allocated for the object, and all
 *      the values will perfectly resemble that of the passed
 *      in MyVector object.
****************************************************************/
template<typename E>
MyVector<E>::MyVector(const MyVector& obj)
{
    sz = obj.sz;
    cap = obj.cap;
    data = new E[cap];
    for (uint64_t i = 0; i < sz; i++)
        data[i] = obj.data[i];
}
//EOF

/****************************************************************
 * 
 *  Method operator=: Class MyVector
 *  //PUBLIC
 * --------------------------------------------------------------
 *  Used when reassigning the value of an already existing 
 *  MyVector object. Will do a deep copy of the passed in
 *  MyVector object.
 * --------------------------------------------------------------
 *  PRE-CONDITIONS
 *      Can apply to objects that either have an lvalue or
 *      rvalue, does not matter.
 * 
 *  POST-CONDITIONS
 *      If the capacity of the calling object is larger than
 *      or equal to the object being passed in, no new memory
 *      will be allocated. Otherwise, previous memory block
 *      will be freed, and new memory block the exact same capacity
 *      as the passed in object will be allocated.
 *      Private attribute "sz" is always changed to be equal to
 *      that of the passed in object.
****************************************************************/
template<typename E>
MyVector<E>& MyVector<E>::operator=(const MyVector<E>& obj)
{
    if (this != &obj) //avoid object assigning to itself
    {
        sz = obj.sz; //sz is assured to be less than or equal to capacity
        if (cap >= obj.cap)
        {
            for (uint64_t i = 0; i < sz; i++)
                data[i] = obj.data[i];
        }
        else
        {
            cap = obj.cap;
            delete [] data;
            data = new E[cap];
            for (uint64_t i = 0; i < sz; i++)
                data[i] = obj.data[i];
        }
    }

    return *this;
}
//EOF

//ADDED FOR CS08

//exactly the same as push_back
template<typename E>
void MyVector<E>::add(const E& value)
{
    push_back(value);
}

template<typename E>
E& MyVector<E>::get(unsigned index)
{
    return at(index);
}

template<typename E>
const E& MyVector<E>::get(unsigned index) const
{
    return at(index);
}

//doubles the size of the dynamic array
//note, in my add function I use the "expand"
//function, which does the exact same.
template<typename E>
void MyVector<E>::resize(void)
{
    expand();
}
#endif //MYVECTOR_CLASS_IMPLENTATION