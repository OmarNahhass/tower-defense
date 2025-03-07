#include "Tower.h"
#include "Map.h"
#include <iostream>
#include <cmath>


Tower::Tower(int x, int y, int cost, int refundValue, int range, int powerAmount, float rateOfFire, sf::Texture& texture)
    : position(x, y), cost(cost), refundValue(refundValue), range(range),
    power(powerAmount), rateOfFire(rateOfFire), level(1), lastShotTime(0) {

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
void Tower::shoot(std::vector<Critter>& critters, float currentTime) {
    if (currentTime - lastShotTime < (1.0f / rateOfFire)) return; // Enforce firing rate


    for (auto& critter : critters) {
     
        // Convert critter position from pixels to grid coordinates
        int critterGridX = critter.getPosition().x / cellSize;
        int critterGridY = critter.getPosition().y / cellSize;

        // Calculate Euclidean distance in grid units
        float dx = critterGridX - position.x;
        float dy = critterGridY - position.y;
        float distance = std::sqrt(dx * dx + dy * dy);


        if (distance <= range) {  
            lastShotTime = currentTime;
            critter.takeDamage(power, currentTime);  // Store hit time
            break;
        }
    }

    // Remove dead critters after loop
    critters.erase(std::remove_if(critters.begin(), critters.end(), [](const Critter& c) { return c.hitPoints <= 0; }), critters.end());
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