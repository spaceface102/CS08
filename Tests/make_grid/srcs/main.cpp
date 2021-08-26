#include "MyGrid.h"
#include <iostream>

int main(void)
{
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "Hello Grid!");
    MyGrid agrid(50, 50, 20);

    window.setFramerateLimit(60);
    while(window.isOpen())
    {
        sf::Event event;
        
        while(window.pollEvent(event)) 
           if (event.type == sf::Event::Closed)
                window.close();

        agrid.displayGrid(window);
        window.display();
    }
    return 0;
}