#include "Tower.h"
#include <iostream>

Tower::Tower(int cost, int refundValue, int range, int power, int rateOfFire)
    : cost(cost), refundValue(refundValue), range(range), power(power), rateOfFire(rateOfFire), level(1) {}

// Virtual destructor implementation
Tower::~Tower() {}

// Shoot method implementation
void Tower::shoot(Critter &target)
{
    target.takeDamage(power); // need to implement critter class (specified in header)
}

// Upgrade method implementation
void Tower::upgrade()
{
    level++;
    power += 10;
    range += 1;
}

int Tower::sell()
{
    return refundValue * level;
}