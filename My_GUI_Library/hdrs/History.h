#ifndef HISTROY_H
#define HISTROY_H

#include <stack>
#include "History_Capable_Types.h"

class History
{
public:
    History(void) = delete;
    History(const History&) = delete;
    ~History(void) = delete;
    History& operator=(const History&) = delete;

    template<typename T>
    static void push(T& data_to_push) noexcept;
    static void pop(void) noexcept;

private:
    static std::stack<History_Capable_Type> stack;
};
std::stack<History_Capable_Type> History::stack;
//EOC

#include "History.cpp"

#endif //HISTROY_H