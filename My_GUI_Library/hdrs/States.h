#ifndef STATES_H
#define STATES_H

#include <cstddef> //std::size_t
#include <cmath>
#include <cassert>

constexpr static std::size_t stateCount(std::size_t last_state)
{
    assert(last_state != 0 && "Can't have a state with no bits activated!");
    return std::log2(last_state) + 1;
}
//EOF

constexpr static std::size_t stateValue(std::size_t state_number)
{
    assert(state_number < 64 && "Max state_number is 63!!! 1UL<<64 is 0!!!");
    return 1UL<<state_number;
}
//EOF

struct States
{
    //NEED TO HAVE 64 BIT NUMBERS FOR EVERY STATE!!!!!
    //TO ADD NEW STATE, DEFINE A STATIC CONSTEXPR STD::SIZE_t
    //VARIABLE, AND USE "stateValue", TO GET CORESPONDING 
    //SPECIFIC VALUE FOR INPUT STATE NUMBER
    //static constexpr std::size_t *your_state* = stateValue(*state number*);

    static constexpr std::size_t hidden         = stateValue(0);
    static constexpr std::size_t highlighted    = stateValue(1);
    static constexpr std::size_t disabled       = stateValue(2);


    //MAKE SURE TO UPDATE WHEN DONE ADDING MORE STATES!!!!!!!!
    //Just input the last state into stateCount function
    static constexpr std::size_t numofstates = stateCount(disabled);
};
//EOC


#endif //STATES_H