#include <SFML/Graphics.hpp>

int main(void)
{
    //sf::VideoMode defines the size of the window
        //the inner size not counting the title bar and borders
        //sf::VideoMode can also fetch the desktop resolution
        //a list of valid video modes for full screen
            //this is in the documentation
    //sf::VideoMode also accepts a third arg which allows you more control
        //you can use multiple options by bitwise OR multiple options
    //Options:
        //sf::Style::None
        //sf::Style::Titlebar
        //
    /*
    sf::Window window(sf::VideoMode(800, 600), "My window");

    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
    }
    */

    //the second arg is the name of the window
    sf::RenderWindow window(sf::VideoMode(300, 300), "Hello World!", sf::Style::Default);

    while(window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
    }

    return 0;
}