#include <stdio.h>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>


#include <SFML/Graphics.hpp>
#include <iostream>

const int ROWS = 10;
const int COLS = 10;
int grid[ROWS][COLS];

// Function to initialize the map with a predefined layout
void initializeMap() {
    // Set all cells to 0 (path)
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            grid[i][j] = 0;
        }
    }

    // Path areas (represented by 1)
    grid[5][0] = 1;
    grid[5][1] = 1;
    grid[5][2] = 1;
    grid[5][3] = 1;
    grid[5][4] = 1;
    grid[4][4] = 1;
    grid[4][5] = 1;
    grid[4][6] = 1;
    grid[4][7] = 1;
    grid[4][8] = 1;
    grid[4][9] = 1;

    // Towers (represented by 2)
    grid[4][3] = 2;
    grid[3][6] = 2;
    grid[5][8] = 2;
}

// Function to display the grid in an SFML window
void displayMap() {
    // Create an SFML window
    sf::RenderWindow window(sf::VideoMode(600, 600), "Tower Defense");

    // Define the size of each grid cell
    const int cellSize = 60;

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

int main() {
    // Initialize and display the map
    initializeMap();
    displayMap();

    return 0;
}
