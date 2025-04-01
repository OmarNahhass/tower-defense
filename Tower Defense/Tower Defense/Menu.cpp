#include "Menu.h"
#include "Map.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>


int selectedMap = 0;
std::vector<std::vector<int>> mapGrid(20, std::vector<int>(20, 0));  // Start with 20x20

bool hasSelectedPreDefinedMap = false;


// 5 pre-determined screen resolutions
std::vector<std::pair<int, int>> resolutions = {
    {800, 600}, {1280, 720}, {1600, 900}, {1920, 980}
};
int resolutionIndex = 0;


int windowWidth = 0;
int windowHeight = 0;

int maxMapWidth = 800;
int maxMapHeight = 600;

int mapWidth = 0;
int mapHeight = 0;

int infoPanelWidth = 0;
int infoPanelHeight = 0;

int numberOfRows = 20;
int numberOfColumns = 20;

int cellSize = 0;

void startMapEditor(int width, int height, int numberOfRows, int numberOfColumns) {

    // Initialize a custom rows x columns map with 0s
    if (!hasSelectedPreDefinedMap) {
        initializeMap(numberOfRows, numberOfColumns);
    }

    displayMap(width, height, numberOfRows, numberOfColumns);  // Render the map 
}

void createMapGrid(int selectedMap) {
    std::vector<std::vector<int>> predefinedMap0 = { // First predefined map
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0},
        {0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0},
        {0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    };

    std::vector<std::vector<int>> predefinedMap1 = { // Second predefined map
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,1,0,0,0,1,0,0,0,1,1,1,1,1,1,1,1,1},
        {0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0},
        {1,1,1,1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,1,0,0,0,1,1,1,1,1,1,0,0,0},
        {0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0},
        {0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,0,0,0},
        {0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0},
        {0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0},
        {0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0},
        {0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    };

    std::vector<std::vector<int>> predefinedMap2 = { // Second predefined map
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0},
        {0,0,1,1,1,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0},
        {0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0},
        {0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0},
        {0,0,1,1,1,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,1,0,0,0,0,1,0,0,1,1,1,1,1,1,0},
        {0,0,0,0,0,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1},
        {0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    };



    // copy the chosen predefined map to the game grid
    if (selectedMap == 0) {
        for (int i = 0; i < 20; i++) {
            for (int j = 0; j < 20; j++) {
                mapGrid[i][j] = predefinedMap0[i][j];
            }
        }
    }
    else if (selectedMap == 1) {
        for (int i = 0; i < 20; i++) {
            for (int j = 0; j < 20; j++) {
                mapGrid[i][j] = predefinedMap1[i][j];
            }
        }
    }
    else if (selectedMap == 2) {
        for (int i = 0; i < 20; i++) {
            for (int j = 0; j < 20; j++) {
                mapGrid[i][j] = predefinedMap2[i][j];
            }
        }
    }
}



void menuScreen() {
    sf::RenderWindow window(sf::VideoMode(1100, 850), "Menu", sf::Style::Titlebar | sf::Style::Close);
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Failed to load font!" << std::endl;
        return;
    }

    sf::Texture mapTextures[3];
    if (!mapTextures[0].loadFromFile("map_1.png") ||
        !mapTextures[1].loadFromFile("map_2.png") ||
        !mapTextures[2].loadFromFile("map_3.png")) {
        std::cerr << "Error loading map images!\n";
    }

    // Create map sprites
    sf::Sprite mapSprites[3];
    for (int i = 0; i < 3; i++) {
        mapSprites[i].setTexture(mapTextures[i]);
        mapSprites[i].setScale(0.5f, 0.5f); 
        mapSprites[i].setPosition(125 + i * 300, 150); // Position map images side by side
    }

    sf::Text title("Game Settings", font, 20);
    title.setFillColor(sf::Color::Black);
    sf::FloatRect titleBounds = title.getLocalBounds();
    title.setOrigin(titleBounds.width / 2, titleBounds.height / 2);
    title.setPosition(window.getSize().x / 2, 40);

    sf::Text selectMap("Select a Predefined Map", font, 28);
    selectMap.setFillColor(sf::Color::Black);
    sf::FloatRect selectMapBounds = selectMap.getLocalBounds();
    selectMap.setOrigin(selectMapBounds.width / 2, selectMapBounds.height / 2);
    selectMap.setPosition(window.getSize().x / 2, 100);

    sf::Text orText("OR", font, 28);
    orText.setFillColor(sf::Color::Black);
    sf::FloatRect orTextBounds = orText.getLocalBounds();
    orText.setOrigin(orTextBounds.width / 2, orTextBounds.height / 2);
    orText.setPosition(window.getSize().x / 2, 450);

    sf::Text resolutionText("Resolution: " + std::to_string(resolutions[resolutionIndex].first) + "x" + std::to_string(resolutions[resolutionIndex].second), font, 18);
    resolutionText.setFillColor(sf::Color::Black);

    sf::Text numberOfRowsText("Number of Rows: " + std::to_string(numberOfRows), font, 18);
    numberOfRowsText.setFillColor(sf::Color::Black);

    sf::Text numberOfColumnsText("Number of Columns: " + std::to_string(numberOfColumns), font, 18);
    numberOfColumnsText.setFillColor(sf::Color::Black);


    sf::Text startButtonText("Create Custom Map", font, 30);
    startButtonText.setFillColor(sf::Color::White);
    sf::FloatRect startButtonBounds = startButtonText.getLocalBounds();
    startButtonText.setOrigin(startButtonBounds.width / 2, startButtonBounds.height / 2);
    startButtonText.setPosition(window.getSize().x / 2, 750);

    sf::RectangleShape startButton(sf::Vector2f(350, 60));
    startButton.setFillColor(sf::Color(100, 100, 255));
    startButton.setOrigin(startButton.getSize().x / 2, startButton.getSize().y / 2);
    startButton.setPosition(window.getSize().x / 2, 750);




    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Up) {
                    resolutionIndex = (resolutionIndex + 1) % resolutions.size();
                }
                else if (event.key.code == sf::Keyboard::Down) {
                    resolutionIndex = (resolutionIndex - 1 + resolutions.size()) % resolutions.size();
                }
                else if (event.key.code == sf::Keyboard::W) {
                    numberOfRows++;
                }
                else if (event.key.code == sf::Keyboard::S && numberOfRows > 10) {
                    numberOfRows--;
                }
                else if (event.key.code == sf::Keyboard::D) {
                    numberOfColumns++;
                }
                else if (event.key.code == sf::Keyboard::A && numberOfColumns > 10) {
                    numberOfColumns--;
                }
            }
            else if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                sf::Vector2f worldMousePos = window.mapPixelToCoords(mousePos);

                // specify the maximum width and height that the map can have
                // the max width and height are calculated to leave enough room for the Info Panel and the Start Game button
                maxMapWidth = (resolutions[resolutionIndex].first * 3) / 4;
                maxMapHeight = (resolutions[resolutionIndex].second * 9) / 10;

                // the dimensions of the screen
                windowWidth = resolutions[resolutionIndex].first;
                windowHeight = resolutions[resolutionIndex].second;


                // Check if a map was clicked
                for (int i = 0; i < 3; i++) {
                    if (mapSprites[i].getGlobalBounds().contains(worldMousePos)) {
                        window.close();

                        // Set the game grid to this map's array
                        selectedMap = i;

                        hasSelectedPreDefinedMap = true;

                        cellSize = std::min(maxMapWidth / 20, maxMapHeight / 20);


                        mapHeight = (resolutions[resolutionIndex].second * 9) / 10;
                        mapWidth = cellSize * 20;

                        // if the map takes less space than expected, the info panel will take up the remaining width
                        infoPanelWidth = windowWidth - mapWidth;
                        infoPanelHeight = mapHeight;

                        createMapGrid(selectedMap);
                        startMapEditor(resolutions[resolutionIndex].first, resolutions[resolutionIndex].second, 20, 20);
                        return;
                    }
                }

                if (startButton.getGlobalBounds().contains(worldMousePos)) {
                    window.close();

                    cellSize = std::min(maxMapWidth / numberOfColumns, maxMapHeight / numberOfRows);


                    mapHeight = (resolutions[resolutionIndex].second * 9) / 10;
                    mapWidth = cellSize * numberOfColumns;

                    // if the map takes less space than expected, the info panel will take up the remaining width
                    infoPanelWidth = windowWidth - mapWidth;
                    infoPanelHeight = mapHeight;

                    startMapEditor(resolutions[resolutionIndex].first, resolutions[resolutionIndex].second, numberOfRows, numberOfColumns);
                    return;
                }
            }
        }

        resolutionText.setString("Resolution (Up/Down): " + std::to_string(resolutions[resolutionIndex].first) + "x" + std::to_string(resolutions[resolutionIndex].second));
        sf::FloatRect resolutionBounds = resolutionText.getLocalBounds();
        resolutionText.setOrigin(resolutionBounds.width / 2, resolutionBounds.height / 2);
        resolutionText.setPosition(window.getSize().x / 2, 550);

        numberOfRowsText.setString("Number of Rows (W/S): " + std::to_string(numberOfRows));
        sf::FloatRect rowsBounds = numberOfRowsText.getLocalBounds();
        numberOfRowsText.setOrigin(rowsBounds.width / 2, rowsBounds.height / 2);
        numberOfRowsText.setPosition(window.getSize().x / 2, 600);

        numberOfColumnsText.setString("Number of Columns (A/D): " + std::to_string(numberOfColumns));
        numberOfColumnsText.setPosition(window.getSize().x / 2, 650);
        sf::FloatRect columnsBounds = numberOfColumnsText.getLocalBounds();
        numberOfColumnsText.setOrigin(columnsBounds.width / 2, columnsBounds.height / 2);
        numberOfColumnsText.setPosition(window.getSize().x / 2, 650);

        window.clear(sf::Color(200, 200, 200));
        window.draw(title);
        window.draw(selectMap);
        window.draw(orText);
        window.draw(resolutionText);
        window.draw(numberOfRowsText);
        window.draw(numberOfColumnsText);
        window.draw(startButton);
        window.draw(startButtonText);

        for (int i = 0; i < 3; i++)
            window.draw(mapSprites[i]);

        window.display();
    }
}
