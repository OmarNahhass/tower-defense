#ifndef TOWER_H
#define TOWER_H

#include "Critter.h"
#include "Strategies.h"

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
    std::unique_ptr<Strategies> strategy;

public:
    static const int cost_DirectDamageTower;
    static const int cost_SlowingTower;
    static const int cost_SniperTower;

    sf::Vector2i position; // Position in the grid
    sf::Sprite sprite; // Tower sprite


    Tower(int x, int y, int cost, int refundValue, int range, int power, float rateOfFire, sf::Texture& texture, std::unique_ptr<Strategies> strat);
    virtual ~Tower(); // Virtual destructor

    Tower(const Tower& other)
        : cost(other.cost), refundValue(other.refundValue), range(other.range), power(other.power), rateOfFire(other.rateOfFire),
        level(other.level), lastShotTime(other.lastShotTime), position(other.position), sprite(other.sprite)
    {
        if (other.strategy) {
            strategy = other.strategy->clone();
        }
    }

    virtual void shoot(std::vector<Critter>& target, float currentTime) = 0;
    virtual int upgrade();
    virtual int sell();

    void setStrategy(std::unique_ptr<Strategies> newStrategy) {
        strategy = std::move(newStrategy);
    }

    void shoot(std::vector<Critter*>& target, float currentTime);
    int getCost();
    int getRefundValue();

    void setPower(int newPower) {
        power = newPower;
    }
    void setRange(int newRange) {
        range = newRange;
    }
    void setRateOfFire(float newRateOfFire) {
        rateOfFire = newRateOfFire;
    }

    virtual int getPower() const { return power; }
    virtual int getRange() const { return range; }
    virtual float getFireRate() const { return rateOfFire; }
};

extern int damageDoneToCritter;

#endif // TOWER_H