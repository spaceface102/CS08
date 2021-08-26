#include "ConwayGameOfLife.h"

int main(void)
{

    sf::RenderWindow window
    (
        sf::VideoMode(1000, 1000), 
        "Conway's Game Of Life!",
        sf::Style::Default ^ sf::Style::Resize
    );

    ConwayGameOfLife game
    (
        {
            {50, 50, 20},
            sf::RectangleShape(),
            {sf::Color::Black, sf::Color::White},
            &window
        }
    );

    while(window.isOpen())
    {
        sf::Event event;

        while(window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        game.generateNextGeneration();
        game.drawConwayGrid();
        window.display();
    }
    return 0;
}