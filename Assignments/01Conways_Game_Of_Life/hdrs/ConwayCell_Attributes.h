#ifndef CONWAY_CELL_ATTRIBUTES_STRUCT_H
#define CONWAY_CELL_ATTRIBUTES_STRUCT_H

#include <SFML/Graphics.hpp>

struct ConwayCell_Attributes
{
    float cell_side_length;
    sf::Color dead_color;
    sf::Color alive_color;
    sf::Color outline_color;
    float outline_thickness_percentage;

        //set default values for cell_attr
    ConwayCell_Attributes(void)
    {
        cell_side_length = 20;
        alive_color = sf::Color::Black;
        dead_color = sf::Color::White;
        outline_color = sf::Color::Black;
        outline_thickness_percentage = 0.05;
    }
};

#endif //CONWAY_CELL_ATTRIBUTES_STRUCT_H