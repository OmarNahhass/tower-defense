#pragma once

#include "Map.h"
#include "Strategies.h"

#include <iostream>



// nearest to the tower
Critter* NearestToTower::selectTarget(std::vector<Critter*>& targets, int towerPosX, int towerPosY) {
    std::cout << "Shooting nearest critter to the tower\n";
    if (targets.empty()) return nullptr;

    Critter* nearest = nullptr;

    float minDistance = mapWidth;

    for (auto& critter : targets) {

        // calculate distance in terms of the grid, not pixels
        int critterGridX = critter->getPosition().x / cellSize;
        int critterGridY = critter->getPosition().y / cellSize;

        float dx = critterGridX - towerPosX;
        float dy = critterGridY - towerPosY;
        float distance = std::sqrt(dx * dx + dy * dy);


        // find new closest critter to tower
        if (distance < minDistance) {
            minDistance = distance;
            nearest = critter;
        }
    }
    
    return nearest;  
}

// nearest to the exit
Critter* NearestToExit::selectTarget(std::vector<Critter*>& targets, int exitPosX, int exitPosY) {
    std::cout << "Shooting nearest critter to the exit\n";
    if (targets.empty()) return nullptr;

    Critter* nearest = nullptr;

    int minPathRemaining = std::numeric_limits<int>::max();

    for (auto& critter : targets) {
        // get each critter's number of remaining path cells until reaching the exit
        int pathRemaining = critter->getRemainingPathCells(); 

        // find new critter closest to the exit
        if (pathRemaining < minPathRemaining) {
            minPathRemaining = pathRemaining;
            nearest = critter;
        }
    }

    return nearest; 
}

// critter with the most amount of health
Critter* StrongestCritter::selectTarget(std::vector<Critter*>& targets) {
    std::cout << "Strongest Critter\n";
    if (targets.empty()) return nullptr;

    Critter* strongest = nullptr;
    int maxHealth = 0;

    for (auto& critter : targets) {

        // find new strongest critter
        if (critter->getHitPoints() > maxHealth) {
            maxHealth = critter->getHitPoints();
            strongest = critter;
        }
    }
    
    return strongest;  
}

// critter with the least amount of health
Critter* WeakestCritter::selectTarget(std::vector<Critter*>& targets) {
    std::cout << "Weakest Critter\n";
    if (targets.empty()) return nullptr;

    Critter* weakest = nullptr;
    int minHealth = 1000;

    for (auto& critter : targets) {

        // find new weakest critter
        if (critter->getHitPoints() < minHealth) {
            minHealth = critter->getHitPoints();
            weakest = critter;
        }
    }

    return weakest;
}