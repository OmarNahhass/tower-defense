#pragma once
#ifndef TOWERDECORATOR_H
#define TOWERDECORATOR_H

#include "Tower.h"

// Base Decorator class
class TowerDecorator : public Tower {
protected:
    std::unique_ptr<Tower> wrappedTower;

public:
    TowerDecorator(std::unique_ptr<Tower> tower)
        : Tower(*tower), wrappedTower(std::move(tower)) {}

    virtual void shoot(std::vector<Critter>& target, float currentTime) override {
        wrappedTower->shoot(target, currentTime);
    }

    virtual void upgrade() override {
        wrappedTower->upgrade();
    }

    virtual int sell() override {
        return wrappedTower->sell();
    }

};

#endif
