#ifndef SPECIAL_TOWERS_H // Header guard
#define SPECIAL_TOWERS_H

#include "Tower.h" // bbase class

// Derived DirectDamageTower class
class DirectDamageTower : public Tower
{
public:
    DirectDamageTower(int x, int y, sf::Texture& texture);
    void shoot(std::vector<Critter>& target, float currentTime) override;
};

// Derived AoETower class
class AoETower : public Tower
{
public:
    AoETower(int x, int y, sf::Texture& texture);
    void shoot(std::vector<Critter>& target, float currentTime) override;
};

// Derived SlowingTower class
class SlowingTower : public Tower
{
public:
    SlowingTower(int x, int y, sf::Texture& texture);
    void shoot(std::vector<Critter>& target, float currentTime) override;
};

#endif