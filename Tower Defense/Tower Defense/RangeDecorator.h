#pragma once
#ifndef RANGEDECORATOR_H
#define RANGEDECORATOR_H

#include "TowerDecorator.h"

// Upgrades a tower by increasing its range
class RangeDecorator : public TowerDecorator {
public:
    RangeDecorator(std::unique_ptr<Tower> tower)
        : TowerDecorator(std::move(tower)) {

        //wrappedTower->setRange(wrappedTower->getRange() + 2);
    }

    int getRange() const override {
        return wrappedTower->getRange();
    }

    void upgrade() override {
        wrappedTower->upgrade();
        wrappedTower->setRange(wrappedTower->getRange() + 2);
    }

    void shoot(std::vector<Critter>& target, float currentTime) override {
        wrappedTower->shoot(target, currentTime);  
    }
};

#endif
