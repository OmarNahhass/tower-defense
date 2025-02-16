#include "Tower.h"
#include "Map.h"
#include <iostream>
#include <cmath>


Tower::Tower(int x, int y, int cost, int refundValue, int range, int power, int rateOfFire, sf::Texture& texture)
    : position(x, y), cost(cost), refundValue(refundValue), range(range),
    power(power), rateOfFire(rateOfFire), level(1), lastShotTime(0) {

    sprite.setTexture(texture);

    // Calculate cell size based on the grid
    int cellSize = WINDOWSIZE / ROWS;

    // Set position to align with the grid
    sprite.setPosition(x * cellSize, y * cellSize);

    // Scale sprite to fit exactly within the grid cell
    sprite.setScale(
        static_cast<float>(cellSize) / sprite.getTexture()->getSize().x,
        static_cast<float>(cellSize) / sprite.getTexture()->getSize().y
    );
}


// Virtual destructor implementation
Tower::~Tower() {}

// Shoot method implementation w/ cooldown
void Tower::shoot(std::vector<Critter>& target, std::vector<sf::VertexArray>& lasers, float currentTime) {
    for (auto& critter : target) {
        float distance = std::hypot(critter.getPosition().x - position.x * 64,
            critter.getPosition().y - position.y * 64);

        if (distance <= range && (currentTime - lastShotTime >= 1.0f / rateOfFire)) {
            critter.takeDamage(power);
            lastShotTime = currentTime;

            // Create a laser beam
            sf::VertexArray laser(sf::Lines, 2);
            laser[0].position = sf::Vector2f(position.x * 64 + 32, position.y * 64 + 32);
            laser[0].color = sf::Color::Red;
            laser[1].position = critter.getPosition();
            laser[1].color = sf::Color::Yellow;

            lasers.push_back(laser);
            break; // Shoot only one critter per frame
        }
    }
}


// Upgrade method implementation
void Tower::upgrade()
{
    level++;
    power += 10;
    range += 1;
}

int Tower::sell()
{
    return refundValue * level;
}