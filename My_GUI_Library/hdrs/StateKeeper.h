#ifndef STATEKEPPER_H
#define STATEKEPPER_H

#include "States.h"

class StateKeeper
{
    static_assert(States::numofstates < sizeof(std::size_t)*8,
    "Need to rethink state keeper to hold more states!");

public:
    StateKeeper(void) noexcept;
    StateKeeper(std::size_t states) noexcept;

    bool isActive(std::size_t states) const;
    void setActive(std::size_t states);
    void setInactive(std::size_t states);

    bool isActive(const StateKeeper& states) const;
    void setActive(const StateKeeper& states);
    void setInactive(const StateKeeper& states);

private:
    std::size_t state_holder;
};

#endif //STATEKEPPER_H