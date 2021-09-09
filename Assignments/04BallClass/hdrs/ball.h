#ifndef BALL_CLASS_H
#define BALL_CLASS_H

#include <SFML/Graphics.hpp>

class Ball : public sf::Drawable
{
public:
    Ball(float radius = 0, std::size_t pointCount = 30);
    void setRadius(float radius);
    void setFillColor(const sf::Color& color);
    void setOutlineColor(const sf::Color& color);
    void setOutlineThickness(float thickness);

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    sf::CircleShape ball;
};

#endif //BALL_CLASS_H