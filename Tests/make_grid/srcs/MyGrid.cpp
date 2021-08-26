#include "MyGrid.h"

MyGrid::MyGrid(unsigned width, unsigned height, float block_side_length)
    : width(width), height(height), block_side_length(block_side_length)
{
    block.setSize(sf::Vector2f(block_side_length, block_side_length));
    block.setFillColor(sf::Color::White);
    block.setOutlineColor(sf::Color::Black);
    block.setOutlineThickness(block_side_length*0.1f);
}
//EOF

void MyGrid::displayGrid(sf::RenderWindow& window)
{
    for (unsigned h = 0; h < height; h++)
        for (unsigned w = 0; w < width; w++)
        {
            block.setPosition(h*block_side_length, w*block_side_length);
            window.draw(block);
        }
}
//EOF

sf::RectangleShape& MyGrid::getBaseBlock(void)
{
    return block;
}