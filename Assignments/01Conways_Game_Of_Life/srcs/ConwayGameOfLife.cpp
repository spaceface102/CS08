#include "ConwayGameOfLife.h"
#include <cassert>
#include <cmath>

ConwayGameOfLife::ConwayGameOfLife(sf::RenderWindow* window_ptr) //default
: window_ptr(window_ptr)
{
    //set default values for cell_attr
    cell_attr.cell_side_length = 20;
    cell_attr.alive_color = sf::Color::Black;
    cell_attr.dead_color = sf::Color::White;
    cell_attr.outline_color = sf::Color::Black;
    cell_attr.outline_thickness_percentage = 0.05;

    //check that window has a size
    assert(window_ptr->getSize() != sf::Vector2u(0, 0));
    set_cell_count(); //set x_cell_count and y_cell_count
    assert(x_cell_count >= 2 && y_cell_count >= 2); //need at least 2 by 2 grid

    current_gen_states.assign(y_cell_count,
        std::vector<bool>(x_cell_count, false)
    );
    next_gen_states = current_gen_states;


    cell.setSize(sf::Vector2f
        (cell_attr.cell_side_length,
        cell_attr.cell_side_length)
    );
    
    cell.setFillColor(cell_attr.dead_color);
    cell.setOutlineColor(cell_attr.outline_color);
    cell.setOutlineThickness(
        cell_attr.outline_thickness_percentage
        *cell_attr.cell_side_length
    );
}
//EOF

ConwayGameOfLife::ConwayGameOfLife(sf::RenderWindow* window_ptr, const ConwayCell& cell_attr)
: window_ptr(window_ptr), cell_attr(cell_attr)
{
    //check that window has a size
    assert(window_ptr->getSize() != sf::Vector2u(0, 0));
    set_cell_count(); //set x_cell_count and y_cell_count
    assert(x_cell_count >= 2 && y_cell_count >= 2); //need at least 2 by 2 grid

    current_gen_states.assign(y_cell_count,
        std::vector<bool>(x_cell_count, false)
    );
    next_gen_states = current_gen_states;


    cell.setSize(sf::Vector2f
        (cell_attr.cell_side_length,
        cell_attr.cell_side_length)
    );
    
    cell.setFillColor(cell_attr.dead_color);
    cell.setOutlineColor(cell_attr.outline_color);
    cell.setOutlineThickness(
        cell_attr.outline_thickness_percentage
        *cell_attr.cell_side_length
    );
}


//MUTATORS
unsigned ConwayGameOfLife::drawCurrentConwayGeneration(void)
{
    unsigned activeCells;

    activeCells = 0;
    for (size_t y = 0; y < current_gen_states.size(); y++)
        for (size_t x = 0; x < current_gen_states[y].size(); x++)
        {
            cell.setPosition(
                x*cell_attr.cell_side_length,
                y*cell_attr.cell_side_length
            );
            if (current_gen_states[y][x])
            {
                //draw cell as alive
                cell.setFillColor(cell_attr.alive_color);
                window_ptr->draw(cell);
                //go back to normal color
                cell.setFillColor(cell_attr.dead_color);
                activeCells++;
            }
            else
                window_ptr->draw(cell);
        }

    return activeCells;
}
//EOF

void ConwayGameOfLife::generateNextGeneration(void)
{
    //CORNERS
        //top left
    updateCellState_NextGen(0, 0, 
          current_gen_states[0][1] 
        + current_gen_states[1][0]
        + current_gen_states[1][1]
    );
        //bottom left
    updateCellState_NextGen(0, y_cell_count - 1,
          current_gen_states[y_cell_count - 2][0]
        + current_gen_states[y_cell_count - 2][1]
        + current_gen_states[y_cell_count - 1][1]
    );
    
        //top right
    updateCellState_NextGen(x_cell_count - 1, 0,
          current_gen_states[0][x_cell_count - 2]
        + current_gen_states[1][x_cell_count - 2]
        + current_gen_states[1][x_cell_count - 1]
    );

        //bottom left
    updateCellState_NextGen(x_cell_count - 1, y_cell_count - 1,
          current_gen_states[y_cell_count - 1][x_cell_count - 2]
        + current_gen_states[y_cell_count - 2][x_cell_count - 2]
        + current_gen_states[y_cell_count - 2][x_cell_count - 1]
    );


    //SIDES
    //left side && right side
    for (size_t y = 1; y < y_cell_count - 1; y++)
    {
        //left side
        updateCellState_NextGen(0, y, 
              current_gen_states[y-1][0]
            + current_gen_states[y-1][1]
            + current_gen_states[y+1][0]
            + current_gen_states[y+1][1]
            + current_gen_states[ y ][1]
        );
        //right side
        updateCellState_NextGen(x_cell_count - 1, y, 
              current_gen_states[y-1][x_cell_count - 1]
            + current_gen_states[y-1][x_cell_count - 2]
            + current_gen_states[y+1][x_cell_count - 1]
            + current_gen_states[y+1][x_cell_count - 2]
            + current_gen_states[ y ][x_cell_count - 2]
        );
    }
    //top side && bottom side
    for (size_t x = 1; x < y_cell_count - 1; x++)
    {
        //top side
        updateCellState_NextGen(x, 0, 
              current_gen_states[0][x-1]
            + current_gen_states[1][x-1]
            + current_gen_states[0][x+1]
            + current_gen_states[1][x+1]
            + current_gen_states[1][ x ]
        );
        //bottom side
        updateCellState_NextGen(x, y_cell_count - 1,
              current_gen_states[y_cell_count - 1][x-1]
            + current_gen_states[y_cell_count - 2][x-1]
            + current_gen_states[y_cell_count - 1][x+1]
            + current_gen_states[y_cell_count - 2][x+1]
            + current_gen_states[y_cell_count - 2][ x ]
        );
    }

    //CENTER
    for (size_t y = 1; y < y_cell_count - 1; y++)
        for (size_t x = 1; x < x_cell_count - 1; x++)
            updateCellState_NextGen(x, y, 
                  current_gen_states[ y ][x+1]
                + current_gen_states[ y ][x-1]
                + current_gen_states[y-1][x+1]
                + current_gen_states[y-1][x-1]
                + current_gen_states[y-1][ x ]
                + current_gen_states[y+1][x+1]
                + current_gen_states[y+1][x-1]
                + current_gen_states[y+1][ x ]
            );


    //sets active the next_gen_states as the current_gen_states
    //therefore anywhere current_gen_states is used, next_gen_states
    //is instead used
    std::swap(current_gen_states, next_gen_states);
}
//EOF

void ConwayGameOfLife::setCellState_VectorIndex(unsigned x, unsigned y, bool state)
{
    if (isValid_VectorIndex(x, y))
        current_gen_states[y][x] = state;
}
//EOF

void ConwayGameOfLife::setCellState_PixelXY(const sf::Vector2u& pixelXY, bool state)
{
    if (isValid_PixelXY(pixelXY))
        current_gen_states[pixelXY.y/cell_attr.cell_side_length]
                          [pixelXY.x/cell_attr.cell_side_length] = state;
}
//EOF

void ConwayGameOfLife::setCellState_PixelXY(unsigned x, unsigned y, bool state)
{
    if (isValid_PixelXY(x, y))
        current_gen_states[y/cell_attr.cell_side_length]
                          [x/cell_attr.cell_side_length] = state;
}

void ConwayGameOfLife::setWindow(sf::RenderWindow* window_ptr)
{
    this->window_ptr = window_ptr;
    //check that window has a size
    assert(window_ptr->getSize() != sf::Vector2u(0, 0));
    set_cell_count(); //set x_cell_count and y_cell_count
    assert(x_cell_count >= 2 && y_cell_count >= 2); //need at least 2 by 2 grid

    current_gen_states.resize(y_cell_count, std::vector<bool>(x_cell_count, false));
    next_gen_states = current_gen_states;
}
//EOF



//HELPERS
inline bool ConwayGameOfLife::isValid_VectorIndex(unsigned x, unsigned y) const
{
    return x < x_cell_count && y < y_cell_count;
}
//EOF

inline bool ConwayGameOfLife::isValid_PixelXY(const sf::Vector2u& pixelXY) const
{
    return
        pixelXY.x < (cell_attr.cell_side_length*x_cell_count)
        && 
        pixelXY.y < (cell_attr.cell_side_length* y_cell_count);
}
//EOF

inline bool ConwayGameOfLife::isValid_PixelXY(unsigned x, unsigned y) const
{
    return
        x < (cell_attr.cell_side_length*x_cell_count)
        && 
        y < (cell_attr.cell_side_length*y_cell_count);
}
//EOF

//PRIVATE HELPER METHODS
inline void ConwayGameOfLife::updateCellState_NextGen(unsigned x, unsigned y, unsigned num_adjacent_cells)
{
    switch (num_adjacent_cells)
    {
        //if already alive, stays alive, if dead, stays dead
        case 2:
            next_gen_states[y][x] = current_gen_states[y][x];
            break;
        //cell will always become/stay alive
        case 3:
            next_gen_states[y][x] = true;
            break;
        //is adjacent to 0, 1, or more than 3 cells, therefore dies
        default:
            next_gen_states[y][x] = false;
            break;
    }
}
//EOF

inline void ConwayGameOfLife::set_cell_count(void)
{
    /*
     *  Math:
     *  (x_cell_count/y_cell_count) = (window.x/window.y)
     *  (x_cell_count)*(y_cell_count)*pow(cell_side_length, 2) = (window.x)*(window.y)
     * 
     *  Goal:
     *  The area of all the cells equals the area provided by the window
    */
    y_cell_count =
            std::sqrt(
                std::pow(window_ptr->getSize().y, 2) /
                std::pow(cell_attr.cell_side_length, 2));

    x_cell_count = 
            (static_cast<double>(window_ptr->getSize().x) /
            window_ptr->getSize().y) * y_cell_count;
}