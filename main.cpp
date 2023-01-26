#include "Grid.h"



int main() {
    Grid myGrid(240, 135, true);

    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Game of Life", sf::Style::Fullscreen);

    sf::Event event{};


    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape)
                    window.close();
                if (event.key.code == sf::Keyboard::Space)
                    myGrid.update();

            }
        }
        window.clear(sf::Color::White);
        myGrid.update();
        myGrid.draw(window);
        window.display();
    }
}
