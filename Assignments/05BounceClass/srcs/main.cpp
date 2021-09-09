#include <SFML/Graphics.hpp>
#include <iostream>
#include "moving.h"
#include "bounce.h"
#include <cstdlib>
#include <ctime>


int main(void)
{
    std::srand(std::time(NULL));
    sf::RenderWindow window({720, 420}, "Hello Bounce!");
    MovingCircle testShape;
    sf::Vector2f velocity;

    velocity.x = (std::rand()%15)+1;
    velocity.y = (std::rand()%15)+1;
    testShape.setVelocityVector2D(velocity);
    testShape.getShape().setRadius(50);
    testShape.getShape().setFillColor(sf::Color::Green);
    testShape.getShape().setPosition({50, 50});
    testShape.getShape().setOrigin({25, 15});

    window.setFramerateLimit(60);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
        {
            sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
            testShape.getShape().setPosition(mousePos);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
        {
            testShape.setVelocityVector2D({testShape.getVelocityVector2D().x*2.0f, testShape.getVelocityVector2D().y*2.0f});
            while(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {} //just do it once, don't register holding down
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
        {
            testShape.setVelocityVector2D({testShape.getVelocityVector2D().x*0.5f, testShape.getVelocityVector2D().y*0.5f});
            while(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {} //just do it once, don't register holding down
        }
        else //only do bounce procedure if user is not moving shape around
        {
            //bounce only updates the testShape's velocity vector,
            //it does not update the position vector
            bounce(testShape, {0.f, 0.f, (float)window.getSize().x, (float)window.getSize().y});
            testShape.updatePosition();
        }
 
        window.clear();
        window.draw(testShape);
        window.display();
    }
    return 0;
}