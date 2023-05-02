//
// Created by anton on 12/12/2022.
//

#include <iostream>
#include "Cell.h"

Cell::Cell(int x, int y, float s, bool m, bool c): posX(x), posY(y), side(s), ageModifier(m), colorModifier(c) {
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
                    color = sf::Color{255, 242, 242}; // Light pink
                    break;
                case 2:
                    color = sf::Color{255, 229, 229}; // Pale pink
                    break;
                case 3:
                    color = sf::Color{255, 217, 217}; // Pink
                    break;
                case 4:
                    color = sf::Color{255, 204, 204}; // Peach-pink
                    break;
                case 5:
                    color = sf::Color{255, 191, 191}; // Dark pink
                    break;
                case 6:
                    color = sf::Color{255, 179, 179}; // Orange-pink
                    break;
                case 7:
                    color = sf::Color{255, 166, 166}; // Light orange
                    break;
                case 8:
                    color = sf::Color{255, 153, 153}; // Salmon pink
                    break;
                case 9:
                    color = sf::Color{255, 140, 140}; // Dark salmon pink
                    break;
                case 10:
                    color = sf::Color{255, 128, 128}; // Coral pink
                    break;
                case 11:
                    color = sf::Color{242, 102, 102}; // Salmon
                    break;
                case 12:
                    color = sf::Color{217, 51, 51}; // Dark salmon
                    break;
                case 13:
                    color = sf::Color{191, 0, 0}; // Red-orange
                    break;
                case 14:
                    color = sf::Color{153, 0, 0}; // Dark red-orange
                    break;
                case 15:
                    color = sf::Color{128, 0, 0}; // Red
            }
            shape.setFillColor(color);
        } else if (colorModifier){
            sf::Color color = sf::Color(R, G, B);
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
        if (neighbor->isAlive()) {
            if (count < 3)
                aliveNeighbors[count] = neighbor;
            count++;
        }
    }
    aliveNeighborsCount = count;
}

void Cell::updateStatus() {
    //Any live cell with fewer than two live neighbours dies, as if by underpopulation
    //Any live cell with two or three live neighbours lives on to the next generation
    //Any live cell with more than three live neighbours dies, as if by overpopulation
    if (alive) {
        if (aliveNeighborsCount != 2 && aliveNeighborsCount != 3) {
            alive = false;
            if (ageModifier)
                age = 0; //if the cell dies, its age is set to 0
        }
        else if (ageModifier) {
            if (age < maxAge)
                age++; //if the cell lives to the next generation, its age is increased by one
            else {
                    alive = false; //if the cell has reached its max age, it dies
                    age = 0;

            }
        }
    }
        //Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction
    else if (!alive && aliveNeighborsCount == 3) {
        alive = true;
        if (ageModifier) {
            age = 0; //if the cell is born, its age is set to 0
        }
        if (colorModifier){
            int r = 0, g = 0, b = 0;
            for (auto cell : aliveNeighbors){
                r += cell->getR();
                g += cell->getG();
                b += cell->getB();
            }
            r = int (r/3);
            g = int (g/3);
            b = int (b/3);
            setColor(r,g,b);
        }
    }
}

void Cell::setColor(int red, int green, int blue) {
    R = red;
    G = green;
    B = blue;
}

int Cell::getR() const {
    return R;
}

int Cell::getG() const {
    return G;
}

int Cell::getB() const {
    return B;
}
