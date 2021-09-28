#ifndef TYPING_CLASS_H
#define TYPING_CLASS_H

#include <SFML/Graphics.hpp>

class Typing : public sf::Drawable
{
public:
    Typing(const sf::Font& font, unsigned characterSize = 30);

    void addEventHandler(const sf::Event& event);
    void update();

private:
    sf::Text drawable_text;
    sf::String normal_text;
    sf::Font font;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

#endif //TYPING_CLASS_H