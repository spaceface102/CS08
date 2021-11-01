#ifndef GUI_COMPONENTS_H
#define GUI_COMPONENTS_H

#include <SFML/Graphics.hpp>
#include "EventHandler.h"
#include "StateKeeper.h"

class GuiComponents : public sf::Drawable, public EventHandler, public StateKeeper
{
};

#endif //GUI_COMPONENTS_H