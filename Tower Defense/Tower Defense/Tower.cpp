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
void Tower::shoot(std::vector<std::unique_ptr<Critter>>& targets, float currentTime) {
    if (strategy) {

        std::vector<Critter*> rawTargets;
        for (auto& critter : targets) {
            rawTargets.push_back(critter.get());  // Convert unique_ptr to raw pointer
        }

        Critter* target = strategy->selectTarget(rawTargets);

        if (target) {
            target->takeDamage(getPower(), currentTime);  // Default damage behavior
        }
    }
}

//void Tower::shoot(std::vector<std::unique_ptr<Critter>>& targets, float currentTime) {
//    float currentTime = currentTime;
//
//    if (currentTime - lastShotTime >= rateOfFire) {
//        sf::Vector2f critterPos = critter->getPosition();
//        float distance = std::hypot(critterPos.x - position.x, critterPos.y - position.y);
//        float bulletSpeed = distance / rateOfFire;  // Ensure bullet reaches target before next shot
//
//        bullet = std::make_unique<Bullet>(position, critterPos, bulletSpeed);
//        lastShotTime = currentTime;
//    }
//}



// Virtual destructor implementation
Tower::~Tower() {}


// Upgrade method implementation
int Tower::upgrade()
{
    level++;
    float scaleFactor = 0.5f; 
    int upgradeCost = static_cast<int>(cost * scaleFactor * level);  
    return upgradeCost;
}

int Tower::sell()
{
    return refundValue * level;
}