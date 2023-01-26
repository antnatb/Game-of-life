//
// Created by anton on 12/12/2022.
//

#include <iostream>
#include "Cell.h"

Cell::Cell(int x, int y, float s): posX(x), posY(y), side(s) {
    shape.setSize({float(side), float(side)});
    shape.setPosition(float(x), float(y));
    shape.setOutlineThickness(0);
    shape.setOutlineColor(sf::Color::Black);
    alive = false;
}

void Cell::addNeighbor(Cell &cell) {
    neighbors.push_back(&cell);
}

void Cell::draw(sf::RenderWindow &window) {
    if (isAlive())
        shape.setFillColor(sf::Color::White);
    else
        shape.setFillColor(sf::Color::Black);
    window.draw(shape);
}

void Cell::countAliveNeighbors() {
    int count = 0;
    for (auto neighbor : neighbors) {
        if (neighbor->isAlive())
            count++;
    }
    aliveNeighbors = count;
}

void Cell::updateStatus() {
    //Any live cell with fewer than two live neighbours dies, as if by underpopulation
    //Any live cell with two or three live neighbours lives on to the next generation
    //Any live cell with more than three live neighbours dies, as if by overpopulation
    if (alive && (aliveNeighbors != 2 && aliveNeighbors != 3))
        alive = false;
    //Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction
    else if (!alive && aliveNeighbors == 3)
        alive = true;
}
