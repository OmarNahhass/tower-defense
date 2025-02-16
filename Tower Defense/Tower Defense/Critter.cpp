#include "Critter.h"

Critter::Critter(int lvl) {
	hitPoints = lvl * 10; //10 hitpoints per level		
	reward = lvl * 5; //5 gold per level
	strength = lvl * 1; // 1 damage per level
	speed = lvl * 1; // +1 speed per level
	level = lvl;
	reachedExit = false;
}

/*
* Method returns true if the critter is killed
*/
bool Critter::takeDamage (int damage) {
    hitPoints -= damage;
    if (hitPoints <= 0) {
        std::cout << "Critter killed! Player earns " << reward << " coins.\n";
        return true;
    }
    else {
        std::cout << "Critter took " << damage << " damage, remaining health: " << hitPoints << "\n";
        return false;
    }
}



