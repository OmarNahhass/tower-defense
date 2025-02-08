#include "game.h"
#include "map.h"

#include <stdio.h>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>


// using the custom map that the user defined earlier in map.cpp, display the final map in-game
void displayGame(sf::RenderWindow& window) {
    int windowLength = 600;
    int cellSize = windowLength / ROWS;

    sf::Color grassColor(80, 109, 25);
    sf::Color pathColor(162, 120, 78);
    sf::Color towerColor(255, 0, 0);

    window.clear(sf::Color::Black);

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            sf::RectangleShape cell(sf::Vector2f(cellSize, cellSize));
            cell.setPosition(j * cellSize, i * cellSize);


            // set cell color based on type (grass, path, tower)
            if (grid[i][j] == 0) cell.setFillColor(grassColor);        // grass
            else if (grid[i][j] == 1) cell.setFillColor(pathColor);    // path
            else if (grid[i][j] == 2) cell.setFillColor(towerColor);   // tower

            window.draw(cell);
        }
    }

    window.display();
}

