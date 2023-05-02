//
// Created by anton on 12/12/2022.
//

#include "Grid.h"
#include "random"



Grid::Grid(int x, int y, bool m, bool c): width(x), height(y), ageModifier(m), colorModifier(c) {
    srand(time(nullptr));
    cellSide = int (sf::VideoMode::getDesktopMode().width) / x;
    for (int i = 0; i < width; i++) {
        cells.emplace_back();
        for (int j = 0; j < height; j++){
            Cell cell(i * cellSide, j * cellSide, float(cellSide), ageModifier, colorModifier);
            if ((static_cast <float> (rand()) / static_cast <float> (RAND_MAX)) <= lifeChance) {
                cell.setAlive(true);
                if (ageModifier)
                    cell.setAge(0);
                if (colorModifier){
                    int r = rand() % 256;
                    int g = rand() % 256;
                    int b = rand() % 256;
                    cell.setColor(r, g, b);
                }
            }
            cells[i].push_back(cell);
        }
    }
    addNeighbors();
}

void Grid::addNeighbors() {
    for (auto& row: cells)
        for (auto& cell: row) {
            int x = cell.getPosX() / cellSide;
            int y = cell.getPosY() / cellSide;
            //left
            if (x - 1 >= 0)
                cell.addNeighbor(cells[x - 1][y]);
            //top left
            if (x - 1 >= 0 && y + 1 < height)
                cell.addNeighbor(cells[x - 1][y + 1]);
            //top
            if (y + 1 < height)
                cell.addNeighbor(cells[x][y + 1]);
            //top right
            if (x + 1 < width && y + 1 < height)
                cell.addNeighbor(cells[x + 1][y + 1]);
            //right
            if (x + 1 < width)
                cell.addNeighbor(cells[x + 1][y]);
            //bottom right
            if (x + 1 < width && y - 1 >= 0)
                cell.addNeighbor(cells[x + 1][y - 1]);
            //bottom
            if (y - 1 >= 0)
                cell.addNeighbor(cells[x][y - 1]);
            //bottom left
            if (x - 1 >= 0 && y - 1 >= 0)
                cell.addNeighbor(cells[x - 1][y - 1]);
        }
}

void Grid::draw(sf::RenderWindow &window) {
    for (auto& row : cells)
        for (auto& cell : row)
            cell.draw(window);
}

void Grid::update() {
    for (auto& row : cells)
        for (auto& cell : row)
            cell.countAliveNeighbors();
    for (auto& row : cells)
        for (auto& cell : row)
            cell.updateStatus();
}
