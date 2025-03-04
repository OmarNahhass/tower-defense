#include "Menu.h"
#include "Map.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>


// 5 pre-determined screen resolutions
std::vector<std::pair<int, int>> resolutions = {
    {800, 600}, {1280, 720}, {1600, 900}, {1920, 1080}, {2560, 1440}
};
int resolutionIndex = 0;


int windowWidth = 0;
int windowHeight = 0;

int mapWidth = 0;
int mapHeight = 0;

int infoPanelWidth = 0;
int infoPanelHeight = 0;

int numberOfRows = 20;
int numberOfColumns = 20;

void startMapEditor(int width, int height, int numberOfRows, int numberOfColumns) {

    // Initialize the map
    initializeMap(numberOfRows, numberOfColumns); // Creates a rows x columns grid and sets all values to 0
    displayMap(width, height, numberOfRows, numberOfColumns);  // Render the map 
}


void menuScreen() {
    sf::RenderWindow window(sf::VideoMode(400, 350), "Menu", sf::Style::Titlebar | sf::Style::Close);
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Failed to load font!" << std::endl;
        return;
    }

    sf::Text title("Game Settings", font, 24);
    title.setPosition(120, 20);
    title.setFillColor(sf::Color::Black);

    sf::Text resolutionText("Resolution: " + std::to_string(resolutions[resolutionIndex].first) + "x" + std::to_string(resolutions[resolutionIndex].second), font, 18);
    resolutionText.setPosition(50, 80);
    resolutionText.setFillColor(sf::Color::Black);

    sf::Text numberOfRowsText("Number of Rows: " + std::to_string(numberOfRows), font, 18);
    numberOfRowsText.setPosition(50, 130);
    numberOfRowsText.setFillColor(sf::Color::Black);

    sf::Text numberOfColumnsText("Number of Columns: " + std::to_string(numberOfColumns), font, 18);
    numberOfColumnsText.setPosition(50, 180);
    numberOfColumnsText.setFillColor(sf::Color::Black);

    sf::Text startButtonText("Customize Map", font, 20);
    startButtonText.setPosition(120, 250);
    startButtonText.setFillColor(sf::Color::White);

    sf::RectangleShape startButton(sf::Vector2f(160, 40));
    startButton.setPosition(120, 250);
    startButton.setFillColor(sf::Color(100, 100, 255));

    sf::Text extraInfoText("(if the number of columns exceeds the number of rows, select a larger screen resolution)", font, 10);
    extraInfoText.setPosition(5, 300);
    extraInfoText.setFillColor(sf::Color::Black);

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
                if (mousePos.x >= startButton.getPosition().x && mousePos.x <= startButton.getPosition().x + startButton.getSize().x &&
                    mousePos.y >= startButton.getPosition().y && mousePos.y <= startButton.getPosition().y + startButton.getSize().y) {
                    window.close();

                    // specify the maximum width and height that the map can have
                    // the max width and height are calculated to leave enough room for the Info Panel and Start Game button
                    int maxMapWidth = (resolutions[resolutionIndex].first * 3) / 4;      
                    int maxMapHeight = (resolutions[resolutionIndex].second * 9) / 10;   

                    // the dimensions of the screen
                    windowWidth = resolutions[resolutionIndex].first;
                    windowHeight = resolutions[resolutionIndex].second;

                    
                    int gridCellSize = std::min(maxMapWidth / numberOfColumns, maxMapHeight / numberOfRows);


                    mapHeight = (resolutions[resolutionIndex].second * 9) / 10;
                    mapWidth = gridCellSize * numberOfColumns;

                    // if the map takes less space than expected, the info panel will take up the remaining width
                    infoPanelWidth = windowWidth - mapWidth;                               
                    infoPanelHeight = (resolutions[resolutionIndex].second * 4) / 5;

                    startMapEditor(resolutions[resolutionIndex].first, resolutions[resolutionIndex].second, numberOfRows, numberOfColumns);
                    return;
                }
            }
        }

        resolutionText.setString("Resolution (Up/Down): " + std::to_string(resolutions[resolutionIndex].first) + "x" + std::to_string(resolutions[resolutionIndex].second));
        numberOfRowsText.setString("Number of Rows (W/S): " + std::to_string(numberOfRows));
        numberOfColumnsText.setString("Number of Columns (A/D): " + std::to_string(numberOfColumns));

        window.clear(sf::Color(200, 200, 200));
        window.draw(title);
        window.draw(resolutionText);
        window.draw(numberOfRowsText);
        window.draw(numberOfColumnsText);
        window.draw(startButton);
        window.draw(startButtonText);
        window.draw(extraInfoText);
        window.display();
    }
}
