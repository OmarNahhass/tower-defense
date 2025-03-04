#include "Menu.h"
#include "Map.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>


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
    //sf::RenderWindow mapWindow(sf::VideoMode(windowSize, windowSize), "Map Editor", sf::Style::Close);

    // Step 1: Initialize the map
    initializeMap(numberOfRows, numberOfColumns); // Creates a numCells x numCells grid and sets all values to 0
    displayMap(width, height, numberOfRows, numberOfColumns);  // Render the map with the given window
}


void menuScreen() {
    sf::RenderWindow window(sf::VideoMode(400, 350), "Settings", sf::Style::Titlebar | sf::Style::Close);
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
                    numberOfRows += 1;
                }
                else if (event.key.code == sf::Keyboard::S && numberOfRows > 10) {
                    numberOfRows -= 1;
                }
                else if (event.key.code == sf::Keyboard::D) {
                    numberOfColumns += 1;
                }
                else if (event.key.code == sf::Keyboard::A && numberOfColumns > 10) {
                    numberOfColumns -= 1;
                }
            }
            else if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                if (mousePos.x >= startButton.getPosition().x && mousePos.x <= startButton.getPosition().x + startButton.getSize().x &&
                    mousePos.y >= startButton.getPosition().y && mousePos.y <= startButton.getPosition().y + startButton.getSize().y) {
                    window.close();

                    windowWidth = resolutions[resolutionIndex].first;
                    windowHeight = resolutions[resolutionIndex].second;

                    mapWidth = (resolutions[resolutionIndex].first * 2) / 3;
                    mapHeight = (resolutions[resolutionIndex].second * 9) / 10;

                    infoPanelWidth = resolutions[resolutionIndex].first / 3;
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
        window.display();
    }
}
