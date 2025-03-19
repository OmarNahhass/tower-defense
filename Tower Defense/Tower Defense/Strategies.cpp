#pragma once

#include "Strategies.h"
#include <iostream>



// nearest to the tower
Critter* NearestToTower::selectTarget(std::vector<Critter*>& targets) {
    std::cout << "Shooting nearest critter to the tower\n";
    if (targets.empty()) return nullptr;

    
    return targets[0];  
}

// nearest to the exit
Critter* NearestToExit::selectTarget(std::vector<Critter*>& targets) {
    std::cout << "Shooting nearest critter to the exit\n";
    if (targets.empty()) return nullptr;

    
    return targets[0]; 
}

// critter with the most health
Critter* StrongestCritter::selectTarget(std::vector<Critter*>& targets) {
    std::cout << "Strongest Critter\n";
    if (targets.empty()) return nullptr;

    Critter* strongest = nullptr;
    int maxHealth = 0;

    for (Critter* critter : targets) {
        if (critter->getHitPoints() > maxHealth) {
            maxHealth = critter->getHitPoints();
            strongest = critter;
        }
    }
    
    return strongest;  
}

// critter with the least health
Critter* WeakestCritter::selectTarget(std::vector<Critter*>& targets) {
    std::cout << "Weakest Critter\n";
    if (targets.empty()) return nullptr;

    
    return targets[0]; 
}