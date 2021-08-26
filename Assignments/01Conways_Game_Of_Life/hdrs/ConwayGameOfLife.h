#ifndef CONWAY_GAME_OF_LIFE_CLASS_H
#define CONWAY_GAME_OF_LIFE_CLASS_H

#include <SFML/Graphics.hpp>
#include <vector>

struct Core_Attributes_Struct
{
    unsigned width;
    unsigned height;
    unsigned cell_size;
};

struct Block_Attributes_Struct
{
    sf::Color alive;
    sf::Color dead;
};

struct ConwayGameAttributes
{
    //these fields can not be modified once set
    const Core_Attributes_Struct core_attributes;
    sf::RectangleShape block;
    Block_Attributes_Struct block_attributes;
    sf::RenderWindow* window_ptr;
};

class ConwayGameOfLife
{
public:
    ConwayGameOfLife(const ConwayGameAttributes& attributes);
    ConwayGameOfLife(void) = delete;

    //Mutators
    unsigned drawConwayGrid(void);
    void generateNextGeneration(void);
    void setCellState_VectorIndex(unsigned x, unsigned y, bool state);
    void setCellState_PixelXY(const sf::Vector2u& pixelXY, bool state);
    void setCellState_PixelXY(unsigned x, unsigned y, bool state);
    ConwayGameAttributes& getGameAttributes(void);

    //Accesors
    const ConwayGameAttributes& getGameAttributes(void) const;

    //Helpers
    inline bool isValid_VectorIndex(unsigned x, unsigned y) const;
    inline bool isValid_PixelXY(const sf::Vector2u& pixelXY) const;
    inline bool isValid_PixelXY(unsigned x, unsigned y) const;

    //Private Helpers
private:
    inline void updateCellState_NextGen(unsigned x, unsigned y, unsigned num_adjacent_cells);

private:
    ConwayGameAttributes attributes;
    std::vector<std::vector<bool>> current_gen_states;
    std::vector<std::vector<bool>> next_gen_states;
};

#endif //CONWAY_GAME_OF_LIFE_CLASS_H