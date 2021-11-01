#include "StateKeeper.h"

StateKeeper::StateKeeper(void) noexcept
    : state_holder(0UL)
{}
//EOF

StateKeeper::StateKeeper(std::size_t states) noexcept
    : state_holder(states)
{}
//EOF

bool StateKeeper::isActive(std::size_t states) const
    {return (this->state_holder) & states;}
//EOF

void StateKeeper::setActive(std::size_t states)
    {this->state_holder |= states;}
//EOF

void StateKeeper::setInactive(std::size_t states)
    {this->state_holder &= ~states;}
//EOF


bool StateKeeper::isActive(const StateKeeper& states) const
    {return (this->state_holder) & (states.state_holder);}

void StateKeeper::setActive(const StateKeeper& states)
    {this->state_holder |= states.state_holder;}
//EOF

void StateKeeper::setInactive(const StateKeeper& states)
    {this->state_holder &= ~states.state_holder;}
//EOF