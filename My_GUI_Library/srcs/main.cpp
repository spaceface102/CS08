#include <iostream>
#include <chrono>
#include "MouseEvents.h"

int main(void)
{
    using namespace std::chrono_literals;
    sf::RenderWindow window{sf::VideoMode{500, 500}, "Hello Gui!"};
    
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (MouseEvents::clickedNTimes_DefaultTimout<3>())
              std::cerr << "Tripple click!\n";
            if (MouseEvents::clickedNTimes<3>(10s))
                std::cerr << "Hit 50 clicks!\n";
        }

        window.clear();
        window.display();
    }
}