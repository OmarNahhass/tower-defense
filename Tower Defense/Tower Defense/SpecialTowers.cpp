#include "SpecialTowers.h"
#include "Map.h"
#include "Tower.h"
#include "Critter.h"

#include <iostream>

// DirectDamageTower constructor
DirectDamageTower::DirectDamageTower(int x, int y, sf::Texture& texture)
    : Tower(x, y, 100, 50, 5, 2, 1, texture) { // Updated to match the new Tower constructor
}

void DirectDamageTower::shoot(std::vector<Critter>& critters, float currentTime) {
    if (currentTime - lastShotTime < (1.0f / rateOfFire)) return; // Enforce firing rate

    int CELL_SIZE = WINDOWSIZE / ROWS;

    for (auto& critter : critters) {

        // Convert critter position from pixels to grid coordinates
        int critterGridX = critter.getPosition().x / CELL_SIZE;
        int critterGridY = critter.getPosition().y / CELL_SIZE;

        // Calculate Euclidean distance in grid units
        float dx = critterGridX - position.x;
        float dy = critterGridY - position.y;
        float distance = std::sqrt(dx * dx + dy * dy);

        /*std::cerr << "Tower at (" << position.x << ", " << position.y
            << ") checking critter at (" << critterGridX << ", " << critterGridY
            << ") | Distance: " << distance << " | Range: " << range << std::endl;*/

        if (distance <= range) {
            //std::cerr << "SHOOT!" << std::endl;
            lastShotTime = currentTime;
            critter.takeDamage(power, currentTime);  // Store hit time
            break;
        }
        else {
            //std::cerr << "NOT SHOOTING!" << std::endl;
        }
    }

    // Remove dead critters after loop
    critters.erase(std::remove_if(critters.begin(), critters.end(),
        [](const Critter& c) { return c.hitPoints <= 0; }),
        critters.end());
}



SlowingTower::SlowingTower(int x, int y, sf::Texture& texture) 
    : Tower(x, y, 150, 125, 2, 0, 1, texture) {
}

// SlowingTower shoot method
void SlowingTower::shoot(std::vector<Critter>& critters, float currentTime)
{
    for (auto& critter : critters) {
        critter.takeDamage(power, currentTime);
        //critter.slowDown();
    }
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
