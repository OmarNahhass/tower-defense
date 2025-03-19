#pragma once

#include "Strategies.h"
#include <iostream>



// Nearest to the tower
Critter* NearestToTower::selectTarget(std::vector<Critter*>& targets) {
    std::cout << "Shooting nearest critter to the tower\n";
    if (targets.empty()) return nullptr;

    
    return targets[0];  
}


Critter* NearestToExit::selectTarget(std::vector<Critter*>& targets) {
    std::cout << "Shooting nearest critter to the exit\n";
    if (targets.empty()) return nullptr;

    
    return targets[0]; 
}


Critter* StrongestCritter::selectTarget(std::vector<Critter*>& targets) {
    std::cout << "Strongest Critter\n";
    if (targets.empty()) return nullptr;

    
    return targets[0];  
}


Critter* WeakestCritter::selectTarget(std::vector<Critter*>& targets) {
    std::cout << "Weakest Critter\n";
    if (targets.empty()) return nullptr;

    
    return targets[0]; 
}