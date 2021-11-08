#ifndef HISTORY_CPP
#define HISTORY_CPP

#include "History.h"
#include <cassert>

template<typename T>
void History::push(T& data_to_push) noexcept
{
    /*
     * Expected input type is a BARETYPE without
     * History_TypeWrapper<your type>() instance,
     * just the pure type. This is done to make
     * use of this class easier!
     * 
     * Careful though, if there ends up being a type
     * in the std::variant without the History_TypeWrapper
     * and the same type with the wrapper, this will cause
     * problems, since it will store the core type in the 
     * variant based Histor_Capable_Type instead of 
     * History_TypeWrapper<your type>
     * 
     * Though, as stated in History_Capable_Types.h
     * EVERY TYPE must be wrapped with
     * History_TypeWrapper<your type>
    */
    stack.push(data_to_push);
}

void History::pop(void) noexcept
{
    //don't do nothing if the stack has been depleted!
    //maybe in the future, it would be wise to have some
    //sort of empty state for the History object
    if (stack.size() == 0)
        return;

    std::visit(
        [](auto& active_node){active_node.restore();},
        stack.top()
    );
    stack.pop();
}

#endif //HISTORY_CPP