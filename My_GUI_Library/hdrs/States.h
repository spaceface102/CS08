#ifndef STATES_H
#define STATES_H

#include <cstddef> //std::size_t
#include <cmath>
#include <cassert>

template<std::size_t state_number>
constexpr static std::size_t stateValue(void)
{
    static_assert(
        state_number < 64 && state_number >= 0,
        "Max state_number is 63!!! 1UL<<64 is 0!!!"
    );
    return 1UL<<state_number;
}
//EOF

struct States
{
    States(void) = delete;
    States(const States&) = delete;
    ~States(void) = delete;
    States& operator=(const States&) = delete;


    //NEED TO HAVE 64 BIT NUMBERS FOR EVERY STATE!!!!!
    //TO ADD NEW STATE, DEFINE A STATIC CONSTEXPR STD::SIZE_t
    //VARIABLE, AND USE "stateValue", TO GET CORESPONDING 
    //SPECIFIC VALUE FOR INPUT STATE NUMBER

    //static constexpr std::size_t *your_state* = stateValue(*state number*);
    static constexpr std::size_t hidden         = stateValue<0>();
    static constexpr std::size_t highlighted    = stateValue<1>();
    static constexpr std::size_t disabled       = stateValue<2>();


    //MAKE SURE TO UPDATE WHEN DONE ADDING MORE STATES!!!!!!!!
    static constexpr std::size_t numofstates = 3;
};
//EOC


#endif //STATES_H