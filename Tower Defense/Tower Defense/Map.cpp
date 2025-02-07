#include "Map.h"

#include <stdio.h>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <SFML/Graphics.hpp>

const int ROWS = 20;
const int COLS = 20;
int grid[ROWS][COLS];

// Function to initialize the map with a predefined layout
void initializeMap() {
    // Set all cells to 0 (path)
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            grid[i][j] = 0;
        }
    }

    // Randomly generate a path from the left to the right side of the screen
    //int startRow = rand() % ROWS; // Random starting row on the left side

    // hard-coded custom path

    for (int i = 0; i < 4; i++)
        grid[10][i] = 1;

    for (int i = 9; i > 6; i--)
        grid[i][3] = 1;

    for (int i = 4; i < 7; i++)
        grid[7][i] = 1;

    for (int i = 8; i < 12; i++)
        grid[i][6] = 1;

    for (int i = 7; i < 12; i++)
        grid[11][i] = 1;

    grid[10][11] = 1;
    grid[9][11] = 1;

    for (int i = 12; i < 20; i++)
        grid[9][i] = 1;



    // Towers (represented by 2)
    /*grid[4][3] = 2;
    grid[3][6] = 2;
    grid[5][8] = 2;*/
}

// Function to display the grid in an SFML window
void displayMap() {
    int windowLength = 600;
    int windowWidth = 600;

    // Create an SFML window
    sf::RenderWindow window(sf::VideoMode(600, 600), "Tower Defense");

    // Define the size of each grid cell
    const int cellSize = windowLength / ROWS;

    // Define colors for different grid values
    sf::Color grassColor(80, 109, 25, 255);  // Green for grass 
    sf::Color pathColor(162, 120, 78, 255);     // Light brown for path
    sf::Color towerColor(255, 0, 0);   // Red for tower colors

    // Main game loop
    while (window.isOpen()) {
        sf::Event event;

        // user closes the window
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear(sf::Color::Black); // Clear the screen with black color

        // Loop through the grid and draw each cell
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                sf::RectangleShape cell(sf::Vector2f(cellSize, cellSize));
                cell.setPosition(j * cellSize, i * cellSize); // Position based on grid

                // Set the color based on grid value
                if (grid[i][j] == 0) {
                    cell.setFillColor(grassColor);
                }
                else if (grid[i][j] == 1) {
                    cell.setFillColor(pathColor);
                }
                else if (grid[i][j] == 2) {
                    cell.setFillColor(towerColor);
                }

                window.draw(cell); // Draw the cell
            }
        }

        window.display(); // Display the map
    }
}
