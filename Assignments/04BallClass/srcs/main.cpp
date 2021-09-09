#include <iostream>
#include <SFML/Graphics.hpp>
#include "ball.h"

int main(void)
{
    sf::RenderWindow window({500, 500, 32}, "Test");
    Ball my_ball;

    my_ball.setFillColor(sf::Color::Blue);
    my_ball.setOutlineColor(sf::Color::Magenta);
    my_ball.setOutlineThickness(-20);
    my_ball.setRadius(100);

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(my_ball);
        window.display();
    }
    return 0;
}