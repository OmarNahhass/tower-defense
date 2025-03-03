#include "MapView.h"
#include "Map.h"

#include <iostream>




void MapView::onCellChanged(int x, int y, int newState) {
    if (newState == 2) {
        towerCount++;
        playerCoins -= 50;
    }
    else if (newState == 0) {
        towerCount--;
        playerCoins += 50;
    }
    
    drawSingleCell(window, x, y, newState, 40);  // Only update this cell
    drawTowerCount(window);
    window.display();
}

void MapView::drawSingleCell(sf::RenderWindow& window, int x, int y, int newState, int cellSize) {

    sf::Sprite sprite;
    sprite.setPosition(x * cellSize, y * cellSize);

    // Draw a thin border for each cell
    sf::RectangleShape border(sf::Vector2f(cellSize, cellSize));
    border.setPosition(x * cellSize, y * cellSize);
    border.setFillColor(sf::Color::Transparent);
    border.setOutlineColor(sf::Color::Black);
    border.setOutlineThickness(1);

    // Set texture based on cell state
    if (newState == 0) sprite.setTexture(grassTextureMap);
    else if (newState == 1) sprite.setTexture(pathTextureMap);
    else if (newState == 2) sprite.setTexture(towerTextureMap);

    sprite.setScale(static_cast<float>(cellSize) / sprite.getTexture()->getSize().x,
        static_cast<float>(cellSize) / sprite.getTexture()->getSize().y);


    window.draw(border);
    window.draw(sprite);
}





void MapView::drawTowerCount(sf::RenderWindow& window) {
    sf::Font font;

    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Error loading font\n";
        return;
    }

    sf::Text towerText;
    towerText.setFont(font);
    towerText.setCharacterSize(20);
    towerText.setFillColor(sf::Color::Black);
    towerText.setPosition(WINDOWSIZE + 15, 20);  // Adjust position as needed
    towerText.setString("Towers: " + std::to_string(towerCount));

    window.draw(towerText);
}

void MapView::drawCoinsCount(sf::RenderWindow& window) {
    sf::Font font;

    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Error loading font\n";
        return;
    }

    sf::Text coinsText;
    coinsText.setFont(font);
    coinsText.setCharacterSize(20);
    coinsText.setFillColor(sf::Color::Black);
    coinsText.setPosition(WINDOWSIZE + 15, 70);  // Adjust position as needed
    coinsText.setString("Coins: " + std::to_string(playerCoins));

    window.draw(coinsText);
}


