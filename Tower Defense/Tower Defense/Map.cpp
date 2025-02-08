#include "Map.h"
#include "Game.h"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>

int grid[ROWS][COLS]; // Define the grid here, not in map.h

void initializeMap() {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            grid[i][j] = 0; // Default to grass (scenery)
        }
    }
}

void handleMouseClick(sf::Vector2i mousePos, sf::Mouse::Button button, int cellSize) {
    int col = mousePos.x / cellSize;
    int row = mousePos.y / cellSize;

    if (col >= 0 && col < COLS && row >= 0 && row < ROWS) {
        if (button == sf::Mouse::Left) {
            grid[row][col] = (grid[row][col] + 1) % 3; // Toggle: Grass → Path → Tower
        }
        else if (button == sf::Mouse::Right) {
            grid[row][col] = 0; // Reset to grass
        }
    }
}

// Placeholder function for the game screen
void startGame() {
    sf::RenderWindow gameWindow(sf::VideoMode(600, 600), "Tower Defense Game");

    while (gameWindow.isOpen()) {
        sf::Event event;
        while (gameWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                gameWindow.close();
            }
        }

        displayGame(gameWindow);  // Pass window reference
    }
}


void displayMap() {
    int windowSize = 600;
    sf::RenderWindow window(sf::VideoMode(windowSize, windowSize + 50), "Tower Defense Map Creation");
    int cellSize = windowSize / ROWS;

    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Failed to load font!" << std::endl;
    }

    sf::RectangleShape button(sf::Vector2f(200, 40));
    button.setPosition((windowSize - 200) / 2, windowSize + 5);
    button.setFillColor(sf::Color(100, 100, 255));

    sf::Text buttonText("Start Game", font, 20);
    buttonText.setPosition((windowSize - 150) / 2, windowSize + 10);
    buttonText.setFillColor(sf::Color::White);

    bool startGameFlag = false;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                if (mousePos.y < windowSize) {
                    handleMouseClick(mousePos, event.mouseButton.button, cellSize);
                }
                else if (mousePos.x >= button.getPosition().x &&
                    mousePos.x <= button.getPosition().x + button.getSize().x &&
                    mousePos.y >= button.getPosition().y &&
                    mousePos.y <= button.getPosition().y + button.getSize().y) {

                    startGameFlag = true; // Set flag instead of closing window
                }
            }
        }

        if (startGameFlag) {
            window.close(); // Close map editor
            return;         // Exit function and let main() handle starting game
        }

        window.clear();

        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                sf::RectangleShape cell(sf::Vector2f(cellSize, cellSize));
                cell.setPosition(j * cellSize, i * cellSize);


                // set cell color based on type (grass, path, tower)
                if (grid[i][j] == 0) cell.setFillColor(sf::Color(80, 109, 25));         // grass
                else if (grid[i][j] == 1) cell.setFillColor(sf::Color(162, 120, 78));   // path
                else if (grid[i][j] == 2) cell.setFillColor(sf::Color::Red);            // tower

                cell.setOutlineColor(sf::Color::Black);
                cell.setOutlineThickness(1);
                window.draw(cell);
            }
        }

        window.draw(button);
        window.draw(buttonText);
        window.display();
    }
}

