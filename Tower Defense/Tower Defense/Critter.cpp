#include "Critter.h"
#include "Map.h"  // Needed for pathCells
#include <iostream>

Critter::Critter(int lvl, sf::Texture& texture) {
    hitPoints = lvl * 10;
    reward = lvl * 5;
    strength = lvl * 1;
    speed = lvl * 10; // Speed per second
    level = lvl;
    reachedExit = false;
    pathIndex = 0;
    moveProgress = 0.0f;

    sprite.setTexture(texture);

    // Ensure the sprite size matches the grid cell size
    float cellSize = static_cast<float>(WINDOWSIZE) / ROWS;
    sprite.setScale(cellSize / sprite.getTexture()->getSize().x,
        cellSize / sprite.getTexture()->getSize().y);

    sprite.setPosition(pathCells[0].x * cellSize, pathCells[0].y * cellSize); // Start at path's beginning
}


/*
* Method returns true if the critter is killed
*/
bool Critter::takeDamage(int damage) {
    hitPoints -= damage;
    if (hitPoints <= 0) {
        std::cout << "Critter killed! Player earns " << reward << " coins.\n";
        return true;
    }
    else {
        std::cout << "Critter took " << damage << " damage, remaining health: " << hitPoints << "\n";
        return false;
    }
}

void Critter::move(float deltaTime) {
    if (this->pathIndex >= pathCells.size() - 1) {
        this->reachedExit = true;
        return;
    }
    float cellSize = static_cast<float>(WINDOWSIZE) / ROWS;
    sf::Vector2f currentPos(pathCells[this->pathIndex].x * cellSize, pathCells[this->pathIndex].y * cellSize);
    sf::Vector2f nextPos(pathCells[this->pathIndex + 1].x * cellSize, pathCells[this->pathIndex + 1].y * cellSize);

    sf::Vector2f direction = nextPos - currentPos;
    float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    if (distance > 0.0f) {
        sf::Vector2f velocity = (direction / distance) * static_cast<float>(speed) * deltaTime;
        sprite.move(velocity);
        moveProgress += speed * deltaTime;

        if (moveProgress >= distance) {
            this->pathIndex++;
            moveProgress = 0.0f;
        }
    }
}






