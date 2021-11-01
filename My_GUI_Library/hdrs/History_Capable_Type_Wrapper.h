#ifndef HISTORY_CAPABLE_TYPE_WRAPPER_H
#define HISTORY_CAPABLE_TYPE_WRAPPER_H

template<typename T>
struct History_TypeWrapper
{
public:
    //DON'T CHANGE ANY TO EXPLICIT CONSTRUCTOR, WILL BREAK
    //HISTORY CLASS, AND USE OF "History_Capable_Type"
    //AKA, typedef of std::variant

    History_TypeWrapper(void) = delete; //avoid default values for data
    History_TypeWrapper(T& data_to_copy) noexcept;
    History_TypeWrapper(const History_TypeWrapper&) noexcept;

    const T data;
    T* const data_ptr;
};

#include "History_Capable_Type_Wrapper.cpp"

#endif //HISTORY_CAPABLE_TYPE_WRAPPER_H