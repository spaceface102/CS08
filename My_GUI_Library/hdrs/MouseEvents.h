#ifndef MOUSE_EVENTS_NAMESPACE
#define MOUSE_EVENTS_NAMESPACE

#include <SFML/Graphics.hpp>
#include <chrono>

namespace MouseEvents
{
    //Special clock wrapper for clickedNTimes() func
    class MyClock
    {
    public:
        MyClock(void) noexcept;
        std::chrono::nanoseconds getElapsedTime(void) noexcept;
        void restart(void) noexcept;

    private:
        typedef std::chrono::steady_clock  my_clock_type;
        decltype(my_clock_type::now()) start;
    };

    //FUNCTIONS
    class clickedNTimes
    {
        clickedNTimes();
    };
    template<
        std::size_t num_clicks,
        std::chrono::milliseconds timeout,
        sf::Mouse::Button button = sf::Mouse::Button::Left
    >
    static bool clickedNTimes(void);
    
    template<std::size_t num_clicks>
    static bool clickedNTimes_DefaultTimout(void);

}

#include "MouseEvents.cpp"

#endif //MOUSE_EVENTS_NAMESPACE