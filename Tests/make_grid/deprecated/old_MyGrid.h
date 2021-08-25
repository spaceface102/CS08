#ifndef MY_OLD_GRID_CLASS_H
#define MY_OLD_GRID_CLASS_H

#include <SFML/Graphics.hpp>

class MyGrid
{
private:
    sf::RectangleShape* grid; //heap allocated 2D-array
    unsigned width;
    unsigned height;
    unsigned gridCapacity; //similar idea as capacity with std::vector
    double block_side_length; //sqrt(blockArea)

public:
    MyGrid(unsigned width, unsigned height, float blockArea);
    MyGrid& operator=(const MyGrid& that);
    MyGrid(const MyGrid& that);
    ~MyGrid(void);
    MyGrid(void) = delete;


    //ACCESSORS
    void displayGrid(sf::RenderWindow& window) const;
    unsigned getWidth(void) const;
    unsigned getHeight(void) const;
    unsigned getBlockSideLength(void) const;

    //MUTATORS
    sf::RectangleShape& at(unsigned x, unsigned y) noexcept(false);
    void setWidth(unsigned width);
    void setHeight(unsigned height);
    void setBlockSideLength(float block_side_length);
};

#endif //MY_OLD_GRID_CLASS_H