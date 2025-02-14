#include "Map.h"
#include "Game.h"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>

#include <queue>

int grid[ROWS][COLS]; // Define the grid here, not in map.h

sf::Texture grassTextureMap, pathTextureMap, towerTextureMap;

void initializeMap() {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            grid[i][j] = 0; // Default to grass (scenery)
        }
    }
}


bool isValidMap() {
    // initialize the coordinates of the entry and exit points
    std::pair<int, int> entry = { -1, -1 };
    std::pair<int, int> exit = { -1, -1 };

    // Find entry and exit points (must be on edges)
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (grid[i][j] == 1) {
                // Check if it's on an edge
                if (i == 0 || i == ROWS - 1 || j == 0 || j == COLS - 1) {
                    if (entry.first == -1) {
                        entry = { i, j };  // First edge path cell is the entry
                    }
                    else if (exit.first == -1) {
                        exit = { i, j };   // Second edge path cell is the exit
                    }
                    else {
                        std::cout << "Invalid map: More than one entry or exit.\n";
                        return false;
                    }
                }
            }
        }
    }

    // entry and/or exit is not on the map
    if (entry.first == -1 || exit.first == -1) {
        std::cout << "Invalid map: Missing entry or exit.\n";
        return false;
    }

    // BFS to check if there's a single connected path
    std::queue<std::pair<int, int>> queue;
    bool visited[ROWS][COLS] = { false };

    // start from entry cell
    queue.push(entry);

    // 2D boolean to check if each cell on the map was visited
    visited[entry.first][entry.second] = true;

    int pathCells = 1;  // Count path cells visited
    int totalPathCells = 0;  // Total path cells in grid

    // move left, right, up ,down
    int directions[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

    for (int i = 0; i < ROWS; i++)
        for (int j = 0; j < COLS; j++)
            if (grid[i][j] == 1) totalPathCells++;

    while (!queue.empty()) {
        std::pair<int, int> current = queue.front();
        queue.pop();

        int currentPositionX = current.first, currentPositionY = current.second;


        // Exit found
        if (currentPositionX == exit.first && currentPositionY == exit.second) {
            return true; 
        }

        // check all adjacent cells from the current cell
        for (int i = 0; i < 4; i++) {

            // move another direction
            int newPositionX = currentPositionX + directions[i][0], newPositionY = currentPositionY + directions[i][1];

            // check if the next cell is 
            // 1- inside the map
            // 2- a path 
            // 3- not visited
            // if the 3 conditions are met, mark the cell as visited and set it to current cell
            if (newPositionX >= 0 && newPositionX < ROWS && newPositionY >= 0 && newPositionY < COLS && grid[newPositionX][newPositionY] == 1 && !visited[newPositionX][newPositionY]) {
                visited[newPositionX][newPositionY] = true;
                queue.push({ newPositionX, newPositionY });
            }
        }
    }

    std::cout << "Invalid map: Entry and exit are not connected.\n";
    return false;
}

// handle the type of cell (grass, path, tower) set by the player
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


    // load images for grass, path and tower
    if (!towerTextureMap.loadFromFile("tower.png") || 
        !grassTextureMap.loadFromFile("grass_3.png") ||
        !pathTextureMap.loadFromFile("path.png")) {
        std::cerr << "Failed to load tower.png!" << std::endl;
    }



    // Start Game button
    sf::RectangleShape button(sf::Vector2f(200, 40));
    button.setPosition((windowSize - 200) / 2, windowSize + 5);
    button.setFillColor(sf::Color(100, 100, 255));

    sf::Text buttonText("Start Game", font, 20);
    buttonText.setPosition((windowSize - 150) / 2, windowSize + 10);
    buttonText.setFillColor(sf::Color::White);

    bool startGameFlag = false;

    while (window.isOpen()) {
        sf::Event event;

        // handle cell type setter
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


        // set images for each cooresponding cell
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {

                sf::Sprite sprite;
                sprite.setPosition(j * cellSize, i * cellSize);

                // Create an outline border
                sf::RectangleShape border(sf::Vector2f(cellSize, cellSize));
                border.setPosition(j * cellSize, i * cellSize);
                border.setFillColor(sf::Color::Transparent);  // Transparent inside
                border.setOutlineColor(sf::Color::Black);     // Black outline
                border.setOutlineThickness(1);                // Outline thickness

                if (grid[i][j] == 0) {
                    sprite.setTexture(grassTextureMap);
                   
                    // Scale the sprite to fit exactly in the cell
                    sprite.setScale(
                        static_cast<float>(cellSize) / grassTextureMap.getSize().x,
                        static_cast<float>(cellSize) / grassTextureMap.getSize().y
                    );

                    window.draw(border);  // Draw the border first
                    window.draw(sprite);  // Draw the sprite on top
                }
                else if (grid[i][j] == 1) {
                    sprite.setTexture(pathTextureMap);

                    // Scale the sprite to fit exactly in the cell
                    sprite.setScale(
                        static_cast<float>(cellSize) / pathTextureMap.getSize().x,
                        static_cast<float>(cellSize) / pathTextureMap.getSize().y
                    );

                    window.draw(border);  // Draw the border first
                    window.draw(sprite);  // Draw the sprite on top
                }
                else if (grid[i][j] == 2) {
                    sprite.setTexture(towerTextureMap);

                    // Scale the sprite to fit exactly in the cell
                    sprite.setScale(
                        static_cast<float>(cellSize) / towerTextureMap.getSize().x,
                        static_cast<float>(cellSize) / towerTextureMap.getSize().y
                    );

                    window.draw(border);  // Draw the border first
                    window.draw(sprite);  // Draw the sprite on top
                }
            }
        }


        window.draw(button);
        window.draw(buttonText);
        window.display();
    }
}

