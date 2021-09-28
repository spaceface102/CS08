#include "typing.h"
#include <iostream>
#include <cctype>

Typing::Typing(const sf::Font& font, unsigned characterSize)
{
    drawable_text.setFont(font);
    drawable_text.setCharacterSize(characterSize);
}

void Typing::addEventHandler(const sf::Event& event)
{
    if (event.type != sf::Event::TextEntered)
        return;
    
    if (event.text.unicode == '\b')
    {
        if (normal_text.getSize() > 0)
            normal_text.erase(normal_text.getSize() - 1);
    }
    else if (event.text.unicode == '\r')
        normal_text += '\n';
    else
        normal_text += event.text.unicode;
}

void Typing::update(void)
{
    drawable_text.setString(normal_text);
}

void Typing::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {target.draw(drawable_text, states);}