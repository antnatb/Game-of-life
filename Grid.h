//
// Created by anton on 12/12/2022.
//

#ifndef GAME_OF_LIFE_GRID_H
#define GAME_OF_LIFE_GRID_H

#include "Cell.h"


class Grid {
public:
    Grid(int x, int y, bool m, bool c);
    ~Grid() = default;

    void addNeighbors();

    void update();

    void draw(sf::RenderWindow &window);

private:
    int width, height;
    int cellSide;
    vector<vector<Cell>> cells;
    float lifeChance = 0.1;
    bool ageModifier;
    bool colorModifier;
};
#endif //GAME_OF_LIFE_GRID_H
