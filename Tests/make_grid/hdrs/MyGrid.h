#ifndef MY_GRID_CLASS_H
#define MY_GRID_CLASS_H

#include <SFML/Graphics.hpp>

class MyGrid
{
private:
    unsigned width;
    unsigned height;
    sf::RectangleShape block;
    float block_side_length;

public:
    MyGrid(void) = delete;
    MyGrid(unsigned width, unsigned height, float block_side_length);

    //Accessors
    void displayGrid(sf::RenderWindow& window);

    //Mutators
    sf::RectangleShape& getBaseBlock(void);
};

#endif //MY_GRID_CLASS_H