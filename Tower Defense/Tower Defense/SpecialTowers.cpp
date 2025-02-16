#include "SpecialTowers.h"
#include "Tower.h"
#include "Critter.h"

#include <iostream>

// DirectDamageTower constructor
DirectDamageTower::DirectDamageTower(int x, int y, sf::Texture& texture)
    : Tower(x, y, 150, 75, 6, 30, 1, texture) { // Updated to match the new Tower constructor
}

void DirectDamageTower::shoot(std::vector<Critter>& target, std::vector<sf::VertexArray>& lasers, float currentTime) {
    std::cout << "Direct Damage Tower shooting at critter!\n";


    for (auto& critter : target) {
        critter.takeDamage(power);
    }

    //target.takeDamage(power);
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