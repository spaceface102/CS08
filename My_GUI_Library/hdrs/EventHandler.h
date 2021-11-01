#ifndef EVENT_HANDLER_INTERFACE_H
#define EVENT_HANDLER_INTERFACE_H

#include <SFML/Graphics.hpp>

class EventHandler
{
public:
    virtual void addEventHandler(const sf::RenderWindow& window, const sf::Event& event) = 0;
    virtual void update(void) = 0;
};

#endif //EVENT_HANDLER_INTERFACE_H