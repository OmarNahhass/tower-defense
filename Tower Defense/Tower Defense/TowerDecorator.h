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
        : Tower(*tower), wrappedTower(std::move(tower)) {
    }

    virtual void shoot(std::vector<std::unique_ptr<Critter>>& target, float currentTime) override {
        wrappedTower->shoot(target, currentTime);
    }

    virtual int upgrade() override {
        return wrappedTower->upgrade();
    }

    virtual int sell() override {
        return wrappedTower->sell();
    }

    int getPower() const override { return wrappedTower->getPower(); }
    int getRange() const override { return wrappedTower->getRange(); }
    float getFireRate() const override { return wrappedTower->getFireRate(); }

};

#endif
