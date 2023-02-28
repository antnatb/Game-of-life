//
// Created by anton on 12/12/2022.
//

#ifndef GAME_OF_LIFE_CELL_H
#define GAME_OF_LIFE_CELL_H

#include "vector"
#include "SFML/Graphics.hpp"

using namespace std;

class Cell {
public:
    Cell(int x, int y, float s, bool m);
    ~Cell() = default;

    bool isAlive() const{
        return alive;
    }
    void setAlive(bool a){
        alive = a;
    }

    void setAge(int a){
        age = a;
    }

    int getPosX() const {
        return posX;
    }
    int getPosY() const {
        return posY;
    }

    void addNeighbor(Cell& cell);
    void countAliveNeighbors();
    void updateStatus();




    void draw(sf::RenderWindow &window);

    sf::RectangleShape shape;

private:
    bool alive;
    int posX, posY;
    float side;
    vector<Cell*> neighbors = {};
    int aliveNeighbors = 0;
    int age = 0;
    static const int maxAge = 3;
    bool ageModifier;
    float deathChance = 0.001;

};


#endif //GAME_OF_LIFE_CELL_H
