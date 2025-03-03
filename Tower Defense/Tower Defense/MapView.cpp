#include "MapView.h"
#include "Map.h"

#include <iostream>

#include <queue>



void MapView::displayInvalidMapScreen(std::string errorMessage) {
    sf::RenderWindow invalidMapWindow(sf::VideoMode(800, 200), "Invalid Map");

    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Failed to load font!" << std::endl;
        return;
    }

    // Game Over text
    sf::Text invalidMapText(errorMessage, font, 25);
    invalidMapText.setFillColor(sf::Color::White);
    invalidMapText.setPosition(0, 75);


    // open new screen with Game Over text
    while (invalidMapWindow.isOpen()) {
        sf::Event event;
        while (invalidMapWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                invalidMapWindow.close();
            }
        }

        invalidMapWindow.clear(sf::Color::Black);
        invalidMapWindow.draw(invalidMapText);
        invalidMapWindow.display();
    }
}



// handle the type of cell (grass, path, tower) set by the player
void MapView::handleMouseClick(sf::Vector2i mousePos, sf::Mouse::Button button, int cellSize) {
    int col = mousePos.x / cellSize;
    int row = mousePos.y / cellSize;

    if (col >= 0 && col < COLS && row >= 0 && row < ROWS) {
        if (button == sf::Mouse::Left) {

            if (grid[row][col] == 2) {                   // decrement counter if previous cell was a tower
                numberOfTowers--;
                playerCoins += 50;
            }

            grid[row][col] = (grid[row][col] + 1) % 3;   // Toggle: Grass ->  Path -> Tower

            if (grid[row][col] == 2) {                   // increment tower counter 
                numberOfTowers++;
                playerCoins -= 50;
            }
        }
        else if (button == sf::Mouse::Right) {

            if (grid[row][col] == 2) {                   // decrement tower counter if current cell is a tower
                numberOfTowers--;
                playerCoins += 50;
            }

            grid[row][col] = 0;                          // Reset to grass
        }
    }
}




// perform BFS to extract the coordinates of the path (from entry to exit)
void MapView::extractPath() {
    pathCells.clear();

    // Locate entry point
    std::pair<int, int> entry = { -1, -1 };

    for (int i = 0; i < COLS; i++) {
        for (int j = 0; j < ROWS; j++) {
            if (grid[i][j] == 1) {
                if (i == 0 || i == COLS - 1 || j == 0 || j == ROWS - 1) {
                    entry = { i, j };
                    break;
                }
            }
        }
        if (entry.first != -1) break;
    }

    if (entry.first == -1) {
        std::cout << "No valid entry point found.\n";
        return;
    }

    std::queue<std::pair<int, int>> queue;
    bool visited[COLS][ROWS] = { false };
    queue.push(entry);
    visited[entry.first][entry.second] = true;

    // Move left, right, up, down
    int directions[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

    while (!queue.empty()) {
        std::pair<int, int> current = queue.front();
        queue.pop();

        int x = current.first, y = current.second;
        pathCells.push_back(sf::Vector2i(y, x)); // Store (column, row)

        for (int i = 0; i < 4; i++) {
            int newX = x + directions[i][0], newY = y + directions[i][1];

            if (newX >= 0 && newX < COLS && newY >= 0 && newY < ROWS &&
                grid[newX][newY] == 1 && !visited[newX][newY]) {
                visited[newX][newY] = true;
                queue.push({ newX, newY });
            }
        }
    }
}
