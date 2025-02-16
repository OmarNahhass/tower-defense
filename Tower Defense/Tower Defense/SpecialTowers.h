#ifndef SPECIAL_TOWERS_H // Header guard
#define SPECIAL_TOWERS_H

#include "Tower.h" // bbase class

// Derived DirectDamageTower class
class DirectDamageTower : public Tower
{
public:
    DirectDamageTower();
    void shoot(Critter& target) override;
};

// Derived AoETower class
class AoETower : public Tower
{
public:
    AoETower();
    void shoot(Critter& target) override;
};

// Derived SlowingTower class
class SlowingTower : public Tower
{
public:
    SlowingTower();
    void shoot(Critter& target) override;
};

#endif