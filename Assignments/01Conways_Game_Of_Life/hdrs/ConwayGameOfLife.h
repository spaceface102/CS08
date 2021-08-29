#ifndef CONWAY_GAME_OF_LIFE_CLASS_H
#define CONWAY_GAME_OF_LIFE_CLASS_H

#include <SFML/Graphics.hpp>
#include "ConwayCell.h"
#include <vector>
class ConwayGameOfLife
{
public:
    ConwayGameOfLife(sf::RenderWindow* window_ptr); //default
    ConwayGameOfLife(sf::RenderWindow* window_ptr, const ConwayCell& cell_attr);
    ConwayGameOfLife(void) = delete;

    //Mutators
    unsigned drawCurrentConwayGeneration(void);
    void generateNextGeneration(void);
    void setCellState_VectorIndex(unsigned x, unsigned y, bool state);
    void setCellState_PixelXY(const sf::Vector2u& pixelXY, bool state);
    void setCellState_PixelXY(unsigned x, unsigned y, bool state);
    void setWindow(sf::RenderWindow* window_ptr);
    
    //Accesors

    //Helpers
    inline bool isValid_VectorIndex(unsigned x, unsigned y) const;
    inline bool isValid_PixelXY(const sf::Vector2u& pixelXY) const;
    inline bool isValid_PixelXY(unsigned x, unsigned y) const;

    //Private Helpers
private:
    inline void updateCellState_NextGen(unsigned x, unsigned y, unsigned num_adjacent_cells);
    inline void set_cell_count(void);

private:
    sf::RenderWindow* window_ptr;
    sf::RectangleShape cell;
    ConwayCell cell_attr;
    unsigned x_cell_count;      //number of cells on x axis
    unsigned y_cell_count;      //number of cells on y axis
    std::vector<std::vector<bool>> current_gen_states;
    std::vector<std::vector<bool>> next_gen_states;
};

#endif //CONWAY_GAME_OF_LIFE_CLASS_H