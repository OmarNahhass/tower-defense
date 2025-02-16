#pragma once
#define CRITTER_H
#include <iostream>

class Critter {
public:
    int hitPoints, reward, strength, speed, level;
    bool reachedExit;

    Critter(int lvl);
    bool takeDamage(int damage);
};


