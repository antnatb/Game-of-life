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
            cell.addNeighbor(cells[(x + width - 1) % width][y]);
            //top left
            cell.addNeighbor(cells[(x + width - 1) % width][(y + height + 1) % height]);
            //top
            cell.addNeighbor(cells[x][(y + height + 1) % height]);
            //top right
            cell.addNeighbor(cells[(x + 1) % width][(y + height + 1) % height]);
            //right
            cell.addNeighbor(cells[(x + 1) % width][y]);
            //bottom right
            cell.addNeighbor(cells[(x + 1) % width][(y + height - 1) % height]);
            //bottom
            cell.addNeighbor(cells[x][(y + height - 1) % height]);
            //bottom left
            cell.addNeighbor(cells[(x + width - 1) % width][(y + height - 1) % height]);
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
