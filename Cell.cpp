//
// Created by anton on 12/12/2022.
//

#include <iostream>
#include "Cell.h"

Cell::Cell(int x, int y, float s, bool m): posX(x), posY(y), side(s), ageModifier(m) {
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
    if (isAlive()) {
        if (ageModifier) {
            sf::Color color;
            switch (age) {
                case 0:
                    color = sf::Color::White;
                    break;
                case 1:
                    color = sf::Color{255, 255, 153}; // light yellow
                    break;
                case 2:
                    color = sf::Color{255, 255, 102}; // yellow
                    break;
                case 3:
                    color = sf::Color{255, 204, 0}; // dark yellow
                    break;
            }
            shape.setFillColor(color);
        } else
            shape.setFillColor(sf::Color::White);
    }
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
    if (alive) {
        if (aliveNeighbors != 2 && aliveNeighbors != 3) {
            alive = false;
            if (ageModifier)
                age = 0; //if the cell dies, its age is set to 0
        }
        else if (ageModifier) {
            if (age < maxAge)
                age++; //if the cell lives to the next generation, its age is increased by one
            else {
                if ((static_cast <float> (rand()) / static_cast <float> (RAND_MAX)) <= deathChance){
                    alive = false; //if the cell has reached its max age, there's a little chance that it dies
                    age = 0;
                }
            }
        }
    }
        //Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction
    else if (!alive && aliveNeighbors == 3) {
        alive = true;
        if (ageModifier)
            age = 0; //if the cell is born, its age is set to 0
    }
}
