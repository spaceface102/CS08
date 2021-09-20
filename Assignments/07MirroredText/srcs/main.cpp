#include <SFML/Graphics.hpp>
#include <iostream>

void printGlobalBounds(const sf::Text& someText)
{
    std::cout
    << "height: " << someText.getGlobalBounds().height << "\n"
    << "left:   " << someText.getGlobalBounds().left << "\n"
    << "top:    " << someText.getGlobalBounds().top << "\n"
    << "width:  " << someText.getGlobalBounds().width << "\n\n";
}

int main(void)
{
    sf::Text text;
    sf::Text mirror;
    sf::Font font;
    sf::Color my_color{0xd1, 0xb9, 0x1f, 0xff};

    sf::RenderWindow window{sf::VideoMode(500, 500), "Yes sir!"};

    if (!font.loadFromFile("OpenSans-Bold.ttf"))
    {
        std::cerr << "Can't find font!\n";
    }
    text.setFont(font);
    text.setString("It Works\n");
    text.setCharacterSize(50);
    text.setFillColor(my_color);
    text.setPosition(50.0f, 250.f);

    printGlobalBounds(text);

    mirror = text;
    mirror.setFillColor({my_color.r, my_color.g, my_color.b, (sf::Uint8)(my_color.a*0.3f)});
    mirror.setScale(1.0f, -0.42f);
    mirror.move(0, text.getCharacterSize()*1.48f);

    printGlobalBounds(mirror);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black);
        window.draw(text);
        window.draw(mirror);
        window.display();
    }

    return 0;
}