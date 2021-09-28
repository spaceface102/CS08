#include <SFML/Graphics.hpp>
#include <iostream>
#include "typing.h"

template<typename T>
std::ostream& operator<<(std::ostream& out, const sf::Rect<T>& rect)
{
    std::cout << "(left, top, width, height) = ("
    << rect.left << ", "
    << rect.top << ", "
    << rect.width << ", "
    << rect.height << ")";
    return out;
}

int main(void)
{
    sf::RenderWindow window{{500, 500, 32}, "Hello Typing!"};
    sf::Font font;

    window.setFramerateLimit(30);
    if (!font.loadFromFile("OpenSans-Bold.ttf"))
        std::cerr << "Could not load font!\n";
    

    Typing typing{font};
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            typing.addEventHandler(event);
        }
        typing.update();

        window.clear();
        window.draw(typing);
        window.display();
    }

    return 0;
}