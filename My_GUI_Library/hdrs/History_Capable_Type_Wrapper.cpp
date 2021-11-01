#ifndef HISTORY_CAPABLE_TYPE_WRAPPER_CPP
#define HISTORY_CAPABLE_TYPE_WRAPPER_CPP

#include "History_Capable_Type_Wrapper.h"

template<typename T>
History_TypeWrapper<T>::History_TypeWrapper(T& data_to_copy) noexcept
    : data(data_to_copy), data_ptr(&data_to_copy)
{}

template<typename T>
History_TypeWrapper<T>::History_TypeWrapper(const History_TypeWrapper<T>& that) noexcept
    : data(that.data), data_ptr(that.data_ptr)
{}

#endif //HISTORY_CAPABLE_TYPE_WRAPPER_CPP