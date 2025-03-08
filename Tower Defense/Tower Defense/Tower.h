#ifndef TOWER_H
#define TOWER_H

#include "Critter.h"
#include <SFML/Graphics.hpp>
#include <vector>

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
    float lastShotTime;

public:
    sf::Vector2i position; // Position in the grid
    sf::Sprite sprite; // Tower sprite


    Tower(int x, int y, int cost, int refundValue, int range, int power, float rateOfFire, sf::Texture& texture);
    virtual ~Tower(); // Virtual destructor

    virtual void shoot(std::vector<Critter>& target, float currentTime);
    void upgrade();
    int sell();
};

extern int damageDoneToCritter;

#endif // TOWER_H