#include "KeyboardShortcuts_Handler.h"
#include <SFML/Graphics.hpp>

bool KeyShortcuts::isUndo(void)
{
    return KeyShortcuts::isAnyCtrl() && sf::Keyboard::isKeyPressed(sf::Keyboard::Z);
}

bool KeyShortcuts::isAnyCtrl(void)
{
    return 
        sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) || 
        sf::Keyboard::isKeyPressed(sf::Keyboard::RControl); 
}