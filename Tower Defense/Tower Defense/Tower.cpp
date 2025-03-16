#include "Tower.h"
#include "Map.h"
#include <iostream>
#include <cmath>

int damageDoneToCritter = 0;


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