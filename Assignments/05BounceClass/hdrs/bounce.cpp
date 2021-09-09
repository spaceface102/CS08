#ifndef BOUNCE_FUNCTION_IMPLENTATION
#define BOUNCE_FUNCTION_IMPLENTATION

#include "bounce.h"

template<typename T>
void bounce(Moving<T>& movingThing, const sf::FloatRect& otherThingBounds)
{
    sf::Vector2f velVect = movingThing.getVelocityVector2D();
    const sf::FloatRect bounds = movingThing.getGlobalBounds();
    //note that use <= 0 and >= window.getSize().x because often, 
    //these will not be equivalent, so just ensuring that you
    //can reach the condition as soon as its dectable is important

    //left side or right side of screen
    if (bounds.left <= otherThingBounds.left || 
        bounds.left + bounds.width >= otherThingBounds.left + otherThingBounds.width)
        velVect.x *= -1;
    //top side of screen
    if (bounds.top <= otherThingBounds.top ||
        bounds.top + bounds.height >= otherThingBounds.top + otherThingBounds.height)
        velVect.y *= -1;

    movingThing.setVelocityVector2D(velVect);
}
//EOF

#endif //BOUNCE_FUNCTION_IMPLENTATION