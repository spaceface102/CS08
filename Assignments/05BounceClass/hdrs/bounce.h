#ifndef BOUNCE_FUNCTION_H
#define BOUNCE_FUNCTION_H

#include "moving.h"
#include <SFML/Graphics.hpp>

template<typename T>
void bounce(Moving<T>& movingThing, const sf::FloatRect& otherThingBounds);

#include "bounce.cpp"

#endif //BOUNCE_FUNCTION_Hb