#include "ConwayGameOfLife.h"
#include <iostream>

int main(void)
{

    sf::RenderWindow window
    (
        sf::VideoMode(1000, 1000), 
        "Conway's Game Of Life!",
        sf::Style::Default ^ sf::Style::Resize
    );

    ConwayGameOfLife game(&window, {40, sf::Color::Black, sf::Color::Red, sf::Color::White, 0.1});

    //Main game loop
    while (window.isOpen())
    {
        sf::Event event;
        unsigned alive_cells;

        std::cout << "Input State:\n"
        << "Left click:  Set cells as active!\n"
        << "Right click: Set cells as NOT active\n"
        << "HIT SPACE TO RUN!\n"
        << "\n"; //spacer
        window.setFramerateLimit(120); //make more responsive to input
        while (window.isOpen() && !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
        {

            while(window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            //Left Click activate cell
            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
                game.setCellState_PixelXY(
                    static_cast<sf::Vector2u>(sf::Mouse::getPosition(window)),
                    true);

            //Right Click un-activate cell
            else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
                game.setCellState_PixelXY(
                    static_cast<sf::Vector2u>(sf::Mouse::getPosition(window)),
                    false);

            window.clear();
            game.drawCurrentConwayGeneration();
            window.display();
        }


        while (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {}

        std::cout << "Running...\n"
        << "HIT SPACE TO STOP RUNNING!\n"
        << "\n"; //spacer
        window.setFramerateLimit(5); //make animation visable
        alive_cells = 1; //make sure to run
        while (window.isOpen() && !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && alive_cells != 0)
        {
            while(window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            window.clear();
            game.generateNextGeneration();
            alive_cells = game.drawCurrentConwayGeneration(); //no alive cells
            window.display();
        }


        while (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {}
    }

    std::cout << "John Conway is a cool dude, RIP.\n";
    std::cout << "Thanks for playing the game!\n";
    return 0;
}