#include "Tower.h"
#include "Map.h"
#include <iostream>
#include <cmath>

int damageDoneToCritter = 0;

const int Tower::cost_DirectDamageTower = 50;
const int Tower::cost_SlowingTower = 150;
const int Tower::cost_SniperTower = 250;


Tower::Tower(int x, int y, int cost, int refundValue, int range, int powerAmount, float rateOfFire, sf::Texture& texture, std::unique_ptr<Strategies> strat)
    : position(x, y), cost(cost), refundValue(refundValue), range(range),
    power(powerAmount), rateOfFire(rateOfFire), level(1), lastShotTime(0),
    strategy(std::move(strat)) {

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
int Tower::getCost() {
    return cost;
}
int Tower::getRefundValue() {
    return refundValue;
}
void Tower::shoot(std::vector<Critter*>& targets, float currentTime) {
    std::cout << "Current Tower Power: " << getPower() << std::endl;

    if (strategy) {

        Critter* target = strategy->selectTarget(targets);

        if (target) {
            target->takeDamage(getPower(), currentTime);  // Default damage behavior
        }
    }
}


// Virtual destructor implementation
Tower::~Tower() {}


// Upgrade method implementation
void Tower::upgrade()
{
    level++;
}

int Tower::sell()
{
    return refundValue * level;
}