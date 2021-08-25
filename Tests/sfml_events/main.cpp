#include <SFML/Graphics.hpp>
#include <iostream>


int main(void)
{
    sf::RenderWindow window(sf::VideoMode(512, 512), "Hello Events!");
    sf::RectangleShape player(sf::Vector2f(100.0f, 100.0f));

    player.setFillColor(sf::Color::Green);
    player.setOrigin(50.0f, 50.0f); //sets where the center of the square is
    window.setFramerateLimit(60);
    while(window.isOpen())
    {
        sf::Event event;

        while(window.pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::Resized:
                    std::cout << "(w, h) = (" 
                        << event.size.width << ", " 
                        << event.size.height << ")\n";
                    break;
                case sf::Event::TextEntered:
                    std::cerr << static_cast<char>(event.text.unicode);
                    break;
            }
        }

        //sf::Keyboard::isKeyPressed in a built in system
        //that allows us to simply integrate key checking
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
        {
            player.move(0.0f, -1.0f);
            player.setFillColor(sf::Color::Red);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
        {
            player.setFillColor(sf::Color::Blue);
            player.move(-1.0f, 0.0f);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
        {
            player.setFillColor(sf::Color::Magenta);
            player.move(0.0f, 1.0f);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        {
            player.setFillColor(sf::Color::Yellow);
            player.move(1.0f, 0.0f);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter))
        {
            player.setFillColor(sf::Color::Green);
            player.setOutlineColor(sf::Color::White);
            player.setOutlineThickness(10.0f);
            player.setPosition(512/2.0f, 512/2.0f);
        }

        if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
        {
            //setPostion either takes an offset like seen with move, or a sf::Vector2f
            //but sf::Mouse::getPosition(window) returns a Vector2i, so we go ahead and type
            //cast it to an acceptable type
            player.setPosition(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)));
        }


        window.clear(); //clears whatever was in the previous "screen"
        //note, the order matters, and having this after drawing basically
        //erases all that you have done.
        window.draw(player);
        window.display();
    }
    return 0;
}