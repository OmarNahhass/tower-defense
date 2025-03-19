#include "Map.h"
#include "Menu.h"
#include "MapView.h"
#include "Game.h"
#include "Tower.h"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>

#include <queue>

int grid[COLS][ROWS]; 
int** mapGrid = nullptr;


#include <vector>
#include <SFML/System/Vector2.hpp>

sf::Texture grassTextureMap, pathTextureMap, towerTextureMap, towerSlowDownTextureMap, towerSniperTextureMap;

std::vector<sf::Vector2i> pathCells, towerCells;


std::vector<MapObserver*> observersMap;


void initializeMap(int numberOfRows, int numberOfColumns) {
    mapGrid = new int* [mapHeight];

    for (int i = 0; i < mapHeight; ++i) {
        mapGrid[i] = new int[mapWidth]; // Allocate each row

        // Initialize all elements to 0
        for (int j = 0; j < mapWidth; ++j) {
            mapGrid[i][j] = 0;
        }
    }
}


void displayInvalidMapScreen(std::string errorMessage) {
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


bool isValidMap() {
    // initialize the coordinates of the entry and exit points
    std::pair<int, int> entry = { -1, -1 };
    std::pair<int, int> exit = { -1, -1 };

    // Find entry and exit points (must be on edges)
    for (int i = 0; i < COLS; i++) {
        for (int j = 0; j < ROWS; j++) {
            if (mapGrid[i][j] == 1) {
                // Check if it's on an edge
                if (i == 0 || i == COLS - 1 || j == 0 || j == ROWS - 1) {
                    if (entry.first == -1) {
                        entry = { i, j };  // First edge path cell is the entry
                    }
                    else if (exit.first == -1) {
                        exit = { i, j };   // Second edge path cell is the exit
                    }
                    else {
                        std::cout << "Invalid map: More than one entry or exit.\n";
                        displayInvalidMapScreen("Invalid map: More than one entry or exit");
                        return false;
                    }
                }
            }
        }
    }

    // entry and/or exit is not on the map
    if (entry.first == -1 || exit.first == -1) {
        std::cout << "Invalid map: Missing entry or exit.\n";
        displayInvalidMapScreen("Invalid map: Missing entry or exit");
        return false;
    }
    

    if (towerCounter == 0) {
        std::cout << "Invalid map: There should be at least 1 tower in the game.\n";
        displayInvalidMapScreen("Invalid map: There should be at least 1 tower in the game");
        return false;
    }

    // BFS to check if there's a single connected path
    std::queue<std::pair<int, int>> queue;
    bool visited[COLS][ROWS] = { false };

    // start from entry cell
    queue.push(entry);

    // 2D boolean to check if each cell on the map was visited
    visited[entry.first][entry.second] = true;

    int pathCells = 1;  // Count path cells visited
    int totalPathCells = 0;  // Total path cells in grid

    // move left, right, up ,down
    int directions[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

    for (int i = 0; i < COLS; i++)
        for (int j = 0; j < ROWS; j++)
            if (mapGrid[i][j] == 1) totalPathCells++;

    while (!queue.empty()) {
        std::pair<int, int> current = queue.front();
        queue.pop();

        int currentPositionX = current.first, currentPositionY = current.second;


        // Exit found
        if (currentPositionX == exit.first && currentPositionY == exit.second && towerCounter >= 1 && playerCoins >= 0) {
            return true; 
        }

        if (playerCoins < 0) {
            std::cout << "You went over the budget. You'll have to sell some of your towers\n";
            displayInvalidMapScreen("You went over the budget. You'll have to sell some of your towers");
            return false;
        }

        // check all adjacent cells 
        for (int i = 0; i < 4; i++) {

            // move another direction
            int newPositionX = currentPositionX + directions[i][0], newPositionY = currentPositionY + directions[i][1];

            // check if the next cell is 
            // 1- inside the map
            // 2- a path 
            // 3- not visited
            // if the 3 conditions are met, mark the cell as visited and set it to current cell
            if (newPositionX >= 0 && newPositionX < COLS && newPositionY >= 0 && newPositionY < ROWS && mapGrid[newPositionX][newPositionY] == 1 && !visited[newPositionX][newPositionY]) {
                visited[newPositionX][newPositionY] = true;
                queue.push({ newPositionX, newPositionY });
            }
        }
    }

    std::cout << "Invalid map: Entry and exit are not connected.\n";
    displayInvalidMapScreen("Invalid map: Entry and exit are not connected");
    return false;
}

// handle the type of cell (grass, path, tower) set by the player
void handleMouseClick(sf::Vector2i mousePos, sf::Mouse::Button button, int cellSize) {
    int col = mousePos.x / cellSize;
    int row = mousePos.y / cellSize;

    if (!(col >= 0 && col < numberOfColumns && row >= 0 && row < numberOfRows))
        return;

    int previousState = mapGrid[row][col];   // original state of the cell
    int newState = previousState;            // start with the same value

    if (button == sf::Mouse::Left) {
        newState = (previousState + 1) % 5;  // grass -> path -> tower -> towerSlowDown -> towerSniper
    }
    else if (button == sf::Mouse::Right) {
        newState = 0;                        // reset to grass
    }

    mapGrid[row][col] = newState;            // apply the new state of the cell

    notifyObservers(col, row, newState, previousState);  
}


// Placeholder function for the game screen
void startGame() {
    sf::RenderWindow gameWindow(sf::VideoMode(windowWidth, windowHeight), "Tower Defense Game", sf::Style::Resize | sf::Style::Close);

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

void drawFullMap(sf::RenderWindow& window, int cellSize, MapView& mapView) {
    for (int i = 0; i < numberOfRows; i++) {
        for (int j = 0; j < numberOfColumns; j++) {
            mapView.drawSingleCell(window, j, i, mapGrid[i][j], cellSize);  // Draw each cell
        }
    }
}



void displayMap(int windowWidth, int windowHeight, int numberOfRows, int numberOfColumns) {

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Tower Defense Map Creation", sf::Style::Resize | sf::Style::Close);

    MapView mapView(window);

    if (observersMap.size() == 0)
        addObserver(&mapView);



    // Load font
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Failed to load font!" << std::endl;
    }




    /* 
    display an info panel on the right with the following:
        - number of towers
        - player coins
        ...
     */

    sf::RectangleShape infoPanel(sf::Vector2f(infoPanelWidth, infoPanelHeight));
    infoPanel.setFillColor(sf::Color(211, 217, 227));
    infoPanel.setPosition(mapWidth, 0);

    // display the tower counter 
    sf::Text towerCountText("Towers: 0", font, 20);
    towerCountText.setFillColor(sf::Color::Black);
    towerCountText.setPosition(mapWidth + 15, 20);

    // display the player coins
    sf::Text playerCoinsText("Coins: " + playerCoins, font, 20);
    playerCoinsText.setFillColor(sf::Color::Black);
    playerCoinsText.setPosition(mapWidth + 15, 70);


    // display the shop
    sf::Text damageTowerCostText("Regular Tower (Green): " + std::to_string(Tower::cost_DirectDamageTower), font, 15);
    damageTowerCostText.setFillColor(sf::Color::Black);
    damageTowerCostText.setPosition(mapWidth + 15, infoPanelHeight - 140);

    sf::Text slowDownTowerCostText("Slow Down Tower (Blue): " + std::to_string(Tower::cost_SlowingTower), font, 15);
    slowDownTowerCostText.setFillColor(sf::Color::Black);
    slowDownTowerCostText.setPosition(mapWidth + 15, infoPanelHeight - 100);

    sf::Text sniperTowerCostText("Sniper Tower (Red): " + std::to_string(Tower::cost_SniperTower), font, 15);
    sniperTowerCostText.setFillColor(sf::Color::Black);
    sniperTowerCostText.setPosition(mapWidth + 15, infoPanelHeight - 60);




    // display the "Start Game" button
    int buttonHeight = windowHeight - mapHeight;

    sf::RectangleShape button(sf::Vector2f(windowWidth, buttonHeight));
    button.setFillColor(sf::Color(100, 100, 255));

    sf::Text buttonText("Start Game", font, 30);
    buttonText.setFillColor(sf::Color::White);

    // Update button and text position after resize
    button.setPosition(0, mapHeight);
    buttonText.setPosition(windowWidth / 2 - 100, mapHeight + 20);





    bool showError = false;
    sf::Clock errorTimer;


    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (event.type == sf::Event::Resized) {
                // Adjust the viewport when the window is resized
                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                window.setView(sf::View(visibleArea));

                maxMapWidth = (event.size.width * 3) / 4;
                maxMapHeight = (event.size.height * 9) / 10;

                
                cellSize = std::min(maxMapWidth / numberOfColumns, maxMapHeight / numberOfRows);

                mapHeight = (event.size.height * 9) / 10;
                mapWidth = cellSize * numberOfColumns;

                // resize and reposition the info panel
                infoPanelWidth = event.size.width - mapWidth;
                infoPanelHeight = mapHeight;
                infoPanel.setSize(sf::Vector2f(infoPanelWidth, infoPanelHeight));
                infoPanel.setPosition(mapWidth, 0);

                // Resize and reposition button
                button.setSize(sf::Vector2f(event.size.width, event.size.height - mapHeight));
                button.setPosition(0, mapHeight);

                unsigned int newFontSize = static_cast<unsigned int>(event.size.height / 25);
                
                // Resize and Reposition button text
                buttonText.setCharacterSize(newFontSize);
                buttonText.setPosition(event.size.width / 2 - 20, mapHeight+20);

                // Resize and reposition the texts in the Info Panel
                towerCountText.setPosition(mapWidth+20, 30);
                playerCoinsText.setPosition(mapWidth + 20, 80);
                damageTowerCostText.setPosition(mapWidth + 20, windowHeight-200);
                slowDownTowerCostText.setPosition(mapWidth + 20, windowHeight - 160);
                sniperTowerCostText.setPosition(mapWidth + 20, windowHeight - 120);
            }
            // handle mouse clicks
            else if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                // clicks handled inside the map
                if (mousePos.y < mapHeight && mousePos.x <= mapWidth) {
                    handleMouseClick(mousePos, event.mouseButton.button, cellSize);
                    showError = false;
                }
                // clicks handled when the "Start Game" button is pressed
                else if (mousePos.x >= button.getPosition().x &&
                    mousePos.x <= button.getPosition().x + button.getSize().x &&
                    mousePos.y >= button.getPosition().y &&
                    mousePos.y <= button.getPosition().y + button.getSize().y) {
                    if (isValidMap()) {
                        window.close();
                        extractPath();
                        currentState = GameState::WaveStart;
                        startGame();
                        return;
                    }
                    else {
                        showError = true;
                        errorTimer.restart();
                    }
                }
            }
        }

        if (showError && errorTimer.getElapsedTime().asSeconds() > 3.0f) {
            showError = false;
        }

        window.clear();



        // Draw info panel
        window.draw(infoPanel);


        // display "Start Game" button
        window.draw(button);
        window.draw(buttonText);

        // display tower counter text
        mapView.drawTowerCount(window);

        // display player coins text
        mapView.drawCoinsCount(window);


        // draw shop info
        window.draw(damageTowerCostText);
        window.draw(slowDownTowerCostText);
        window.draw(sniperTowerCostText);


        drawFullMap(window, cellSize, mapView);  

        window.display();
    }
}










// perform BFS to extract the coordinates of the path (from entry to exit)
void extractPath() {
    pathCells.clear();

    // Locate entry point
    std::pair<int, int> entry = { -1, -1 };

    for (int i = 0; i < COLS; i++) {
        for (int j = 0; j < ROWS; j++) {
            if (mapGrid[i][j] == 1) {
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
                mapGrid[newX][newY] == 1 && !visited[newX][newY]) {
                visited[newX][newY] = true;
                queue.push({ newX, newY });
            }
        }
    }
}




void addObserver(MapObserver* observer) {
    observersMap.push_back(observer);
}

void removeObserver(MapObserver* observer) {
    observersMap.erase(std::remove(observersMap.begin(), observersMap.end(), observer), observersMap.end());
}

void notifyObservers(int column, int row, int newState, int previousState) {
    for (MapObserver* observer : observersMap) {
        observer->onCellChanged(column, row, newState, previousState);
    }
}