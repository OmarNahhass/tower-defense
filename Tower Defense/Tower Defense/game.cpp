#include "game.h"
#include "map.h"

#include <stdio.h>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#include <iostream>

sf::Texture grassTextureGame, pathTextureGame, towerTextureGame;


// using the custom map that the user defined earlier in map.cpp, display the final map in-game
void displayGame(sf::RenderWindow& window) {
    int cellSize = WINDOWSIZE / ROWS;

    sf::Texture texture;
    if (!towerTextureGame.loadFromFile("tower.png") ||
        !grassTextureGame.loadFromFile("grass_3.png") ||
        !pathTextureGame.loadFromFile("path.png")) {
        std::cerr << "Failed to load tower.png!" << std::endl;
    }

    window.clear(sf::Color::Black);


    // display images for each corresponding cell
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {

            sf::Sprite sprite;
            sprite.setPosition(j * cellSize, i * cellSize);

            // Create an outline border
            sf::RectangleShape border(sf::Vector2f(cellSize, cellSize));

            if (grid[i][j] == 0) {
                sprite.setTexture(grassTextureGame);

                // Scale the sprite to fit exactly in the cell
                sprite.setScale(
                    static_cast<float>(cellSize) / grassTextureGame.getSize().x,
                    static_cast<float>(cellSize) / grassTextureGame.getSize().y
                );

                window.draw(sprite);  // Draw the sprite on top
            }
            else if (grid[i][j] == 1) {
                sprite.setTexture(pathTextureGame);

                // Scale the sprite to fit exactly in the cell
                sprite.setScale(
                    static_cast<float>(cellSize) / pathTextureGame.getSize().x,
                    static_cast<float>(cellSize) / pathTextureGame.getSize().y
                );

                window.draw(sprite);  // Draw the sprite on top
            }
            else if (grid[i][j] == 2) {
                sprite.setTexture(towerTextureGame);

                // Scale the sprite to fit exactly in the cell
                sprite.setScale(
                    static_cast<float>(cellSize) / towerTextureGame.getSize().x,
                    static_cast<float>(cellSize) / towerTextureGame.getSize().y
                );

                window.draw(sprite);  // Draw the sprite on top
            }
        }
    }

    window.display();
}

