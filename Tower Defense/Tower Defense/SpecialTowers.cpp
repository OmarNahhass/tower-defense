#include "SpecialTowers.h"
#include "Map.h"
#include "Tower.h"
#include "Critter.h"

#include <iostream>

// DirectDamageTower constructor
DirectDamageTower::DirectDamageTower(int x, int y, sf::Texture& texture)
    : Tower(x, y, 150, 75, 6, 30, 1, texture) { // Updated to match the new Tower constructor
}

void DirectDamageTower::shoot(std::vector<Critter>& critters, float currentTime) {
    if (currentTime - lastShotTime < 1.0f / rateOfFire) return;  // Enforce firing rate

    for (auto& critter : critters) {
        // Convert critter position from pixels to grid coordinates
        int critterGridX = critter.getPosition().x / (WINDOWSIZE / ROWS);
        int critterGridY = critter.getPosition().y / (WINDOWSIZE / COLS);

        float dx = critterGridX - position.x;
        float dy = critterGridY - position.y;
        float distance = std::sqrt(dx * dx + dy * dy);

        if (distance <= range) {  // Check if within tower range
            std::cout << "Direct Damage Tower hitting critter!\n";
            critter.takeDamage(power, currentTime);
            critter.setHitTime(currentTime);  // Mark as recently hit for red border effect
        }
    }

    lastShotTime = currentTime;  // Update shot timer
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
//
//SlowingTower::SlowingTower() : Tower(200, 100, 4, 10, 1) {}
//
//// SlowingTower shoot method
//void SlowingTower::shoot(Critter& target)
//{
//    target.takeDamage(power);
//    target.slowDown();
//}