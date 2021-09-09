#include "ball.h"

Ball::Ball(float radius, std::size_t pointCount) : ball(radius, pointCount) {}
//EOF

void Ball::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(ball, states);
}
//EOF

void Ball::setRadius(float radius)
{
    ball.setRadius(radius);
}
//EOF

void Ball::setFillColor(const sf::Color& color)
{
    ball.setFillColor(color);
}
//EOF

void Ball::setOutlineColor(const sf::Color& color)
{
    ball.setOutlineColor(color);
}
//EOF

void Ball::setOutlineThickness(float thickness)
{
    ball.setOutlineThickness(thickness);
}
//EOF