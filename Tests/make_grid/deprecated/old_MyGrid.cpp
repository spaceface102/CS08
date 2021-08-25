#include "old_MyGrid.h"
#include <cmath>
#include <stdexcept>

MyGrid::MyGrid(unsigned width, unsigned height, float blockArea) :
    width(width), height(height)
{

    gridCapacity = height*width;
    block_side_length = std::sqrt(blockArea);
    grid = new sf::RectangleShape[gridCapacity];

    for (unsigned h = 0; h < height; h++)
        for (unsigned w = 0; w < width; w++)
        {
            grid[(h*width) + w].setSize(
                sf::Vector2f(block_side_length, block_side_length)
            );
            grid[(h*width) + w].setPosition(
                h*block_side_length, w*block_side_length
            );
            grid[(h*width) + w].setOutlineColor(sf::Color::Black);
            grid[(h*width) + w].setOutlineThickness(0.1f * block_side_length);
        }
}
//EOF

MyGrid::~MyGrid(void)
{
    delete [] grid;
}
//EOF

MyGrid::MyGrid(const MyGrid& that)
{
    gridCapacity = that.gridCapacity;
    grid = new sf::RectangleShape[gridCapacity];
    *this = that;
}
//EOF

MyGrid& MyGrid::operator=(const MyGrid& that)
{
    if (&that == this)
        return *this;
    
    //Always copied memory
    width = that.width;
    height = that.height;
    block_side_length = that.block_side_length;

    //avoid reallocating memory
    if (gridCapacity >= that.gridCapacity)
    {
        //gridCapacity remains the same since all the memory
        //is still allocated and available. Will allow to
        //go back to a larger size without needing to reallocate
        //memory
        for (unsigned h = 0; h < height; h++)
            for (unsigned w = 0; w < width; w++)
                grid[(h*width) + w] = that.grid[(h*width) + w];
    }
    else //for sure have to allocate more memory
    {
        //now has to change since that.gridCapacity is bigger
        gridCapacity = width*height;
        delete [] grid;
        grid = new sf::RectangleShape[gridCapacity];

        for (unsigned h = 0; h < height; h++)
            for (unsigned w = 0; w < width; w++)
                grid[(h*width) + w] = that.grid[(h*width) + w];
    }

    return *this;
}
//EOF

void MyGrid::displayGrid(sf::RenderWindow& window) const
{
    for (unsigned h = 0; h < height; h++)
        for (unsigned w = 0; w < width; w++)
            window.draw(grid[(h*width) + w]);
}

unsigned MyGrid::getWidth(void) const
{
    return width;
}
//EOF

unsigned MyGrid::getHeight(void) const
{
    return height;
}
//EOF

unsigned MyGrid::getBlockSideLength(void) const
{
    return block_side_length;
}
//EOF

sf::RectangleShape& MyGrid::at(unsigned x, unsigned y) noexcept(false)
{
    if (x >= height || y >= width)
        throw std::out_of_range("Invalid index for MyGrid object");

    return grid[(x*width) + y];
}
//EOF

void MyGrid::setWidth(unsigned width)
{
    this->width = width;
}
//EOF

void MyGrid::setHeight(unsigned height)
{
    this->height = height;
}
//EOF

void MyGrid::setBlockSideLength(float block_side_length)
{
    for (unsigned h = 0; h < height; h++)
        for (unsigned w = 0; w < width; w++)
            grid[(h*width) + w].setSize(
                sf::Vector2f(block_side_length, block_side_length)
            );
}
//EOF
