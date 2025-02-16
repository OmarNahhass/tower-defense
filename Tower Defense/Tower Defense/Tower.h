#ifndef TOWER_H
#define TOWER_H

#include "Critter.h"

class Critter;

// Base Tower class
class Tower
{
protected:
    int cost;
    int refundValue;
    int range;
    int power;
    int rateOfFire;
    int level;

public:
    Tower(int cost, int refundValue, int range, int power, int rateOfFire);
    virtual ~Tower(); // Virtual destructor

    virtual void shoot(Critter& target);
    void upgrade();
    int sell();
};

#endif // TOWER_H