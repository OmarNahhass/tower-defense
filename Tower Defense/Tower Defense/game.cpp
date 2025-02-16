#include "game.h"
#include "map.h"

#include <stdio.h>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#include <iostream>

#include "Critter.h"

#include <vector>

sf::Texture grassTextureGame, pathTextureGame, towerTextureGame, critterTexture;


std::vector<Critter> critters; // List of active critters




void spawnCritter() {
    critters.emplace_back(1, critterTexture); // Spawn a Level 1 critter
}

void updateCritters(float deltaTime) {
    for (auto& critter : critters) {
        critter.move(deltaTime, pathCells);
    }
}

void drawCritters(sf::RenderWindow& window) {
    for (const auto& critter : critters) {
        window.draw(critter.sprite);
    }
}


// using the custom map that the user defined earlier in map.cpp, display the final map in-game
void displayGame(sf::RenderWindow& window) {
    int cellSize = WINDOWSIZE / ROWS;

    if (!towerTextureGame.loadFromFile("tower.png") ||
        !grassTextureGame.loadFromFile("grass_3.png") ||
        !pathTextureGame.loadFromFile("path.png") || 
        !critterTexture.loadFromFile("critter.jpg")) {

        std::cerr << "Failed to load texture!" << std::endl;
    }

    window.clear(sf::Color::Black);

    sf::Clock clock;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        float deltaTime = clock.restart().asSeconds();

        window.clear(sf::Color::Black);

        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                sf::Sprite sprite;
                sprite.setPosition(j * cellSize, i * cellSize);

                if (grid[i][j] == 0) {
                    sprite.setTexture(grassTextureGame);
                }
                else if (grid[i][j] == 1) {
                    sprite.setTexture(pathTextureGame);
                }
                else if (grid[i][j] == 2) {
                    sprite.setTexture(towerTextureGame);
                }

                sprite.setScale(
                    static_cast<float>(cellSize) / sprite.getTexture()->getSize().x,
                    static_cast<float>(cellSize) / sprite.getTexture()->getSize().y
                );

                window.draw(sprite);
            }
        }

        // Spawn a critter every 5 seconds
        static float spawnTimer = 0.0f;
        spawnTimer += deltaTime;
        if (spawnTimer >= 5.0f) {
            spawnTimer = 0.0f;
            spawnCritter();
        }

        updateCritters(deltaTime);
        drawCritters(window);

        window.display();
    }
}


