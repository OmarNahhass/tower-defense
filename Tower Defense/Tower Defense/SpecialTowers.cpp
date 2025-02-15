#include "SpecialTowers.h"
#include <iostream>

DirectDamageTower::DirectDamageTower() : Tower(100, 50, 3, 20, 2) {}

// DirectDamageTower shoot method
void DirectDamageTower::shoot(Critter &target)
{
    target.takeDamage(power); // Direct damage
}

// AoETower constructor - critter implementationS
AoETower::AoETower() : Tower(150, 75, 2, 15, 3) {}

void AoETower::shoot(Critter &target)
{

    target.takeDamage(power);

    for (Critter *nearbyCritter : getNearbyCritters(target.getPosition(), range))
    {
        if (nearbyCritter != &target)
        {                                         // Avoid damaging the primary target twice
            nearbyCritter->takeDamage(power / 2); // Example: Deal half damage to nearby critters
        }
    }
}

SlowingTower::SlowingTower() : Tower(200, 100, 4, 10, 1) {}

// SlowingTower shoot method
void SlowingTower::shoot(Critter &target)
{
    target.takeDamage(power);
    target.slowDown();
}