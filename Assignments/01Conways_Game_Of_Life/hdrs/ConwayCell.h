#ifndef CONWAY_CELL_STRUCT_H
#define CONWAY_CELL_STRUCT_H

#include <SFML/Graphics.hpp>

struct ConwayCell
{
    float cell_side_length;
    sf::Color dead_color;
    sf::Color alive_color;
    sf::Color outline_color;
    float outline_thickness_percentage;
};

#endif //CONWAY_CELL_STRUCT_H