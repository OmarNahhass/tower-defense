#include "Critter.h"
#include "Map.h"  // Needed for pathCells
#include "Game.h"
#include <iostream>



void displayGameOverScreen() {
    sf::RenderWindow gameOverWindow(sf::VideoMode(400, 200), "Game Over");

    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Failed to load font!" << std::endl;
        return;
    }

    // Game Over text
    sf::Text gameOverText("Game Over", font, 20);
    gameOverText.setFillColor(sf::Color::White);
    gameOverText.setPosition(50, 100);


    // open new screen with Game Over text
    while (gameOverWindow.isOpen()) {
        sf::Event event;
        while (gameOverWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                gameOverWindow.close();
                exit(0); // Close the game 
            }
        }

        gameOverWindow.clear(sf::Color::Black);
        gameOverWindow.draw(gameOverText);
        gameOverWindow.display();
    }
}


Critter::Critter(int lvl, sf::Texture& texture) {
    hitPoints = lvl * 10;
    reward = lvl * 10;
    strength = lvl * 1;
    speed = lvl * 10; // Speed per second
    level = lvl;
    reachedExit = false;
    pathIndex = 0;
    moveProgress = 0.0f;


    hitTime = 0;  // Initialize hit time
    hitDuration = 0.75f;  // Red border stays for 0.75s

}

sf::Vector2f Critter::getPosition() const {
    return sprite.getPosition();
}


/*
* Method returns true if the critter is killed
*/
bool Critter::takeDamage(int damage, float currentTime) {
    
    if (damage > 0) {  // Only update when actually hit
        hitPoints -= damage;
        hitTime = currentTime;
        std::cout << "Critter took " << damage << " damage, remaining health: " << hitPoints << "\n";
    }

    if (hitPoints <= 0) {
        std::cout << "Critter killed! Player earns " << reward << " coins.\n";
        numberOfCrittersRemaining--;
        playerCoins += reward;
        return true;
    }

    return false;
}


// Check if critter is still in "hit" state (for red border effect)
bool Critter::isHit(float currentTime) const {
    return (currentTime - hitTime) <= hitDuration;
}

void Critter::move(float deltaTime) {
    if (this->pathIndex >= pathCells.size() - 1) {
        this->reachedExit = true;

        displayGameOverScreen(); // Display Game Over screen
        return;
    }

    
    /*sprite.setScale(cellSize / sprite.getTexture()->getSize().x, cellSize / sprite.getTexture()->getSize().y);*/

    sf::Vector2f currentPos(pathCells[this->pathIndex].x * cellSize, pathCells[this->pathIndex].y * cellSize);
    sf::Vector2f nextPos(pathCells[this->pathIndex + 1].x * cellSize, pathCells[this->pathIndex + 1].y * cellSize);

    sf::Vector2f direction = nextPos - currentPos;
    float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);


    if (distance > 0.0f) {
        sf::Vector2f velocity = (direction / distance) * static_cast<float>(speed) * deltaTime;
        moveProgress += speed * deltaTime;

        if (moveProgress >= distance) {
            this->pathIndex++;
            moveProgress = 0.0f;
        }
        notifyMoved(velocity);
    }
}

void Critter::addObserver(CritterObserver* observer, sf::Texture& texture) {
    observers.push_back(observer);
    notifyAdded(texture);
}

void Critter::removeObserver(CritterObserver* observer) {
    observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
}

void Critter::notifyMoved(sf::Vector2f velocity) {

    for (auto* observer : observers) {
        observer->onCritterMoved(*this, velocity);
    }
}

void Critter::notifyAdded(sf::Texture& texture) {
    for (auto* observer : observers) {
        observer->onCritterAdded(*this, texture);
    }
}



