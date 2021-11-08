#ifndef MOUSE_EVENTS_CPP
#define MOUSE_EVENTS_CPP

#include "MouseEvents.h"
#include <cassert>

namespace MouseEvents
{

MyClock::MyClock(void) noexcept
    : start(my_clock_type::now())
{}

std::chrono::nanoseconds MyClock::getElapsedTime(void) noexcept
{
    return my_clock_type::now() - start;
}

void MyClock::restart(void) noexcept
{
    start = my_clock_type::now();
}

template<std::size_t num_clicks>
static bool MouseEvents::clickedNTimes_DefaultTimout(void)
{
    //enables suffix for time constants 
    using namespace std::chrono_literals;
    
    //to add another, just follow the else if constexpr pattern
    if constexpr(num_clicks == 2)
        return clickedNTimes<num_clicks, 250ms>();
    else if constexpr (num_clicks == 3)
        return clickedNTimes<num_clicks, 450ms>();
}

template<std::size_t num_clicks, std::chrono::milliseconds timeout, sf::Mouse::Button button = sf::Mouse::Button::Left>
static bool MouseEvents::clickedNTimes(void)
{
    static_assert(
        num_clicks >= 2, 
        "Can only use this function when counting more than one click!"
    );

    static MouseEvents::MyClock clock;
    static std::size_t count_clicks = 0;

    if (sf::Mouse::isButtonPressed(button))
    {
        //first click, or the start of a new cycle
        //from a midway click that took too long
        if (
            count_clicks == 0 ||
            clock.getElapsedTime() > timeout)
        {
            clock.restart();
            count_clicks = 1;
            return false;
        }
        //third click happened in the allowed time
        else if (count_clicks == num_clicks - 1)
        {
            //reset
            count_clicks = 0;
            return true;
        }
        //2 or up to N - 1 clicks still within the time limit
        else
        {
            count_clicks++;
            return false;
        }
    }

    //no click at all
    return false;
}

} //namespace MouseEvents

#endif //MOUSE_EVENTS_CPP