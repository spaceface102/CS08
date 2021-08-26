#include "ConwayGameOfLife.h"
#include <cassert>

ConwayGameOfLife::ConwayGameOfLife(const ConwayGameAttributes& attributes)
    : attributes(attributes)
{
    //Make sure we are ok to run! Need a 2x2 grid at minimum
    //Can turn off in release build with -DNDEBUG compiler option
    assert
    (
        this->attributes.core_attributes.cell_size >= 2
        && this->attributes.core_attributes.height >= 2
        && this->attributes.core_attributes.width >= 2
    );


    current_gen_states.assign
    (
        attributes.core_attributes.height,
        std::vector<bool>(attributes.core_attributes.width, false)
    );
    next_gen_states = current_gen_states;


    this->attributes.block.setSize(sf::Vector2f
    (
        attributes.core_attributes.cell_size,
        attributes.core_attributes.cell_size)
    );
    this->attributes.block.setFillColor(attributes.block_attributes.dead);
    this->attributes.block.setOutlineColor(attributes.block_attributes.alive);
    this->attributes.block.setOutlineThickness(0.1f*attributes.core_attributes.cell_size);
}
//EOF








//MUTATORS
unsigned ConwayGameOfLife::drawConwayGrid(void)
{
    unsigned activeCells;

    activeCells = 0;
    for (size_t y = 0; y < current_gen_states.size(); y++)
        for (size_t x = 0; x < current_gen_states[y].size(); x++)
        {
            attributes.block.setPosition(
                x*attributes.core_attributes.cell_size,
                y*attributes.core_attributes.cell_size
            );
            if (current_gen_states[y][x])
            {
                //draw cell as alive
                attributes.block.setFillColor(attributes.block_attributes.alive);
                attributes.window_ptr->draw(attributes.block);
                //go back to normal color
                attributes.block.setFillColor(attributes.block_attributes.dead);
                activeCells++;
            }
            else
                attributes.window_ptr->draw(attributes.block);
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
    updateCellState_NextGen(0, attributes.core_attributes.height - 1,
          current_gen_states[attributes.core_attributes.height - 2][0]
        + current_gen_states[attributes.core_attributes.height - 2][1]
        + current_gen_states[attributes.core_attributes.height - 1][1]
    );
    
        //top right
    updateCellState_NextGen(attributes.core_attributes.width - 1, 0,
          current_gen_states[0][attributes.core_attributes.width - 2]
        + current_gen_states[1][attributes.core_attributes.width - 2]
        + current_gen_states[1][attributes.core_attributes.width - 1]
    );

        //bottom left
    updateCellState_NextGen(attributes.core_attributes.width - 1, attributes.core_attributes.height - 1,
          current_gen_states[attributes.core_attributes.height - 1][attributes.core_attributes.width - 2]
        + current_gen_states[attributes.core_attributes.height - 2][attributes.core_attributes.width - 2]
        + current_gen_states[attributes.core_attributes.height - 2][attributes.core_attributes.width - 1]
    );


    //SIDES
    //left side && right side
    for (size_t y = 1; y < attributes.core_attributes.height - 1; y++)
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
        updateCellState_NextGen(attributes.core_attributes.width - 1, y, 
              current_gen_states[y-1][attributes.core_attributes.width - 1]
            + current_gen_states[y-1][attributes.core_attributes.width - 2]
            + current_gen_states[y+1][attributes.core_attributes.width - 1]
            + current_gen_states[y+1][attributes.core_attributes.width - 2]
            + current_gen_states[ y ][attributes.core_attributes.width - 2]
        );
    }
    //top side && bottom side
    for (size_t x = 1; x < attributes.core_attributes.height - 1; x++)
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
        updateCellState_NextGen(x, attributes.core_attributes.height - 1,
              current_gen_states[attributes.core_attributes.height - 1][x-1]
            + current_gen_states[attributes.core_attributes.height - 2][x-1]
            + current_gen_states[attributes.core_attributes.height - 1][x+1]
            + current_gen_states[attributes.core_attributes.height - 2][x+1]
            + current_gen_states[attributes.core_attributes.height - 2][ x ]
        );
    }

    //CENTER
    for (size_t y = 1; y < attributes.core_attributes.height - 1; y++)
        for (size_t x = 1; x < attributes.core_attributes.width - 1; x++)
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
        current_gen_states[pixelXY.y/attributes.core_attributes.cell_size]
                          [pixelXY.x/attributes.core_attributes.cell_size] = state;
}
//EOF

void ConwayGameOfLife::setCellState_PixelXY(unsigned x, unsigned y, bool state)
{
    if (isValid_PixelXY(x, y))
        current_gen_states[y/attributes.core_attributes.cell_size]
                          [x/attributes.core_attributes.cell_size] = state;
}

ConwayGameAttributes& ConwayGameOfLife::getGameAttributes(void)
{
    return attributes;
}
//EOF







//ACCESORS
const ConwayGameAttributes& ConwayGameOfLife::getGameAttributes(void) const
{
    return attributes;
}







//HELPERS
inline bool ConwayGameOfLife::isValid_VectorIndex(unsigned x, unsigned y) const
{
    return
    (
            x < attributes.core_attributes.width
        &&
            y < attributes.core_attributes.height
    );
}
//EOF

inline bool ConwayGameOfLife::isValid_PixelXY(const sf::Vector2u& pixelXY) const
{
    return
    (
        pixelXY.x < (attributes.core_attributes.cell_size
                    * attributes.core_attributes.width   )
        && 
        pixelXY.y < (attributes.core_attributes.cell_size
                    * attributes.core_attributes.height  )
    );
}
//EOF

inline bool ConwayGameOfLife::isValid_PixelXY(unsigned x, unsigned y) const
{
    return
    (
        x < (attributes.core_attributes.cell_size
            * attributes.core_attributes.width   )
        && 
        y < (attributes.core_attributes.cell_size
            * attributes.core_attributes.height  )
    );
}
//EOF

//PRIVATE HELPER METHODS
inline void ConwayGameOfLife::updateCellState_NextGen(unsigned x, unsigned y, unsigned num_adjacent_cells)
{
    switch (num_adjacent_cells)
    {
        //if already alive, stays alive, if dead, stays dead
        case 2:
            next_gen_states[y][x] = current_gen_states[y][y];
        //cell will always become/stay alive
        case 3:
            next_gen_states[y][x] = true;
            break;
        //is adjacent to 0, 1, or more than 3 cells, therefore dies
        default:
            next_gen_states[y][x] = false;
    }
}
//EOF