#include "SpecialTowers.h"
#include "Map.h"
#include "Tower.h"
#include "Critter.h"
#include "Strategies.h"

#include <iostream>

// DirectDamageTower constructor
DirectDamageTower::DirectDamageTower(int x, int y, sf::Texture& texture)
    : Tower(x, y, 50, 40, numberOfColumns/5, 2, 1, texture, std::make_unique<NearestToTower>()) { // Updated to match the new Tower constructor
}
// DirectDamageTower shoot method
void DirectDamageTower::shoot(std::vector<std::unique_ptr<Critter>>& critters, float currentTime) {
    if (currentTime - lastShotTime < (1.0f / rateOfFire)) return; // Enforce firing rate


    std::vector<Critter*> inRangeCritters;

    // find critter in range
    for (auto& critter : critters) {
        int critterGridX = critter->getPosition().x / cellSize;
        int critterGridY = critter->getPosition().y / cellSize;

        float dx = critterGridX - position.x;
        float dy = critterGridY - position.y;
        float distance = std::sqrt(dx * dx + dy * dy);

        if (distance <= range) {
            inRangeCritters.push_back(critter.get());
        }
    }

    
    if (inRangeCritters.empty()) return;  // No targets available

    Critter* target = nullptr;

    // determine which critter to attack
    if (inRangeCritters.size() == 1) {    // only one critter in range, attack directly
        target = inRangeCritters[0];
    }
    else if (strategy) {                  // multiple critters, use strategy
       
        target = strategy->selectTarget(inRangeCritters, position.x, position.y);
    }

    // apply damage
    if (target) {
        lastShotTime = currentTime;
        target->takeDamage(getPower(), currentTime);
    }

    // Remove dead critters after loop
    critters.erase(std::remove_if(critters.begin(), critters.end(),
        [](const Critter& c) { return c.hitPoints <= 0; }),
        critters.end());
}




// SlowingTower constructor
SlowingTower::SlowingTower(int x, int y, sf::Texture& texture) 
    : Tower(x, y, 150, 100, 2, 0, 10, texture, std::make_unique<NearestToExit>()) {
}

// SlowingTower shoot method
void SlowingTower::shoot(std::vector<std::unique_ptr<Critter>>& critters, float currentTime)
{
    if (currentTime - lastShotTime < (1.0f / rateOfFire)) return; // Enforce firing rate


    for (auto& critter : critters) {

        // Convert critter position from pixels to grid coordinates
        int critterGridX = critter->getPosition().x / cellSize;
        int critterGridY = critter->getPosition().y / cellSize;

        // Calculate Euclidean distance in grid units
        float dx = critterGridX - position.x;
        float dy = critterGridY - position.y;
        float distance = std::sqrt(dx * dx + dy * dy);


        if (distance <= range) {
            //std::cerr << "SHOOT!" << std::endl;
            lastShotTime = currentTime;
            critter->slowDown(currentTime);  // Store hit time
            break;
        }
    }
}



// SniperTower constructor
SniperTower::SniperTower(int x, int y, sf::Texture& texture)
    : Tower(x, y, 250, 200, numberOfColumns/2, 10, 15, texture, std::make_unique<StrongestCritter>()) {
}
// SniperTower shoot method
void SniperTower::shoot(std::vector<std::unique_ptr<Critter>>& critters, float currentTime) {
    if (currentTime - lastShotTime < (1.0f / rateOfFire)) return; // Enforce firing rate


    for (auto& critter : critters) {

        // Convert critter position from pixels to grid coordinates
        int critterGridX = critter->getPosition().x / cellSize;
        int critterGridY = critter->getPosition().y / cellSize;

        // Calculate Euclidean distance in grid units
        float dx = critterGridX - position.x;
        float dy = critterGridY - position.y;
        float distance = std::sqrt(dx * dx + dy * dy);


        if (distance <= range) {
            //std::cerr << "SHOOT!" << std::endl;
            lastShotTime = currentTime;
            critter->takeDamage(power, currentTime);  // Store hit time
            break;
        }
    }

    // Remove dead critters after loop
    critters.erase(std::remove_if(critters.begin(), critters.end(),
        [](const Critter& c) { return c.hitPoints <= 0; }),
        critters.end());
}




// AoETower constructor - critter implementationS
// 
// 
// 
// 
// 
//AoETower::AoETower() : Tower(150, 75, 2, 15, 3) {}







//void AoETower::shoot(Critter& target)
//{
//
//    target.takeDamage(power);
//
//    for (Critter* nearbyCritter : getNearbyCritters(target.getPosition(), range))
//    {
//        if (nearbyCritter != &target)
//        {                                         // Avoid damaging the primary target twice
//            nearbyCritter->takeDamage(power / 2); // Example: Deal half damage to nearby critters
//        }
//    }
//}
