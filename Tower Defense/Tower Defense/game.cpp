#include "game.h"
#include "map.h"
#include "Critter.h"
#include "Tower.h"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

sf::Texture grassTextureGame, pathTextureGame, towerTextureGame, critterTexture;

std::vector<Critter> critters;  // List of critters
std::vector<Tower> towers;      // List of towers
std::vector<sf::VertexArray> lasers; // Active lasers

std::vector<sf::Vector2i> towerPositions;


void spawnCritter() {
    critters.emplace_back(1, critterTexture);
}

void storeTowerPositions() {
    towerPositions.clear(); // Reset before scanning

    for (int j = 0; j < COLS; j++) {  // Column first
        for (int i = 0; i < ROWS; i++) {  // Then row
            if (grid[i][j] == 2) { // Tower cell
                towerPositions.emplace_back(j, i); // Store (x, y) correctly
            }
        }
    }
}


void spawnTowers() {
    towers.clear(); // Clear old towers before spawning new ones

    for (const auto& pos : towerPositions) {
        towers.emplace_back(pos.x, pos.y, 100, 50, 200, 20, 2, towerTextureGame);
    }
}


void updateCritters(float deltaTime) {
    for (auto& critter : critters) {
        critter.move(deltaTime);
    }
}

// Update towers to shoot at critters
void updateTowers(float currentTime) {
    lasers.clear(); // Reset laser effects each frame

    for (auto& tower : towers) {
        tower.shoot(critters, lasers, currentTime);
    }
}

// Draw towers
void drawTowers(sf::RenderWindow& window) {
    for (const auto& tower : towers) {
        window.draw(tower.sprite);
    }
}

// Draw lasers
void drawLasers(sf::RenderWindow& window) {
    for (const auto& laser : lasers) {
        window.draw(laser);
    }
}

// Draw critters
void drawCritters(sf::RenderWindow& window) {
    for (const auto& critter : critters) {
        window.draw(critter.sprite);
    }
}

// Display the game
void displayGame(sf::RenderWindow& window) {
    if (!towerTextureGame.loadFromFile("tower.png") ||
        !grassTextureGame.loadFromFile("grass_3.png") ||
        !pathTextureGame.loadFromFile("path.png") ||
        !critterTexture.loadFromFile("critter.jpg")) {

        std::cerr << "Failed to load texture!" << std::endl;
    }

    storeTowerPositions(); // Store all tower positions before spawning
    spawnTowers();         // Spawn towers at stored positions

    window.clear(sf::Color::Black);
    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        float deltaTime = clock.restart().asSeconds();
        float currentTime = clock.getElapsedTime().asSeconds();

        window.clear(sf::Color::Black);


        // Draw the grid
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                sf::Sprite sprite;

                // Corrected positioning (column = x, row = y)
                int cellSize = WINDOWSIZE / ROWS;
                sprite.setPosition(j * cellSize, i * cellSize);

                // Assign the correct texture
                if (grid[i][j] == 0) {
                    sprite.setTexture(grassTextureGame);
                }
                else if (grid[i][j] == 1) {
                    sprite.setTexture(pathTextureGame);
                }

                // Ensure texture is set before calling getSize()
                if (sprite.getTexture() != nullptr) {
                    sprite.setScale(
                        static_cast<float>(cellSize) / sprite.getTexture()->getSize().x,
                        static_cast<float>(cellSize) / sprite.getTexture()->getSize().y
                    );
                }

                window.draw(sprite);
            }
        }


        // Spawn critters every 5 seconds
        static float spawnTimer = 0.0f;
        spawnTimer += deltaTime;
        if (spawnTimer >= 5.0f) {
            spawnTimer = 0.0f;
            spawnCritter();
        }

        updateCritters(deltaTime);
        updateTowers(currentTime);

        drawCritters(window);
        drawTowers(window);
        drawLasers(window);

        window.display();
    }
}

