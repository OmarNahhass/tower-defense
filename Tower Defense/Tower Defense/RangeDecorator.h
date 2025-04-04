#pragma once
#ifndef RANGEDECORATOR_H
#define RANGEDECORATOR_H

#include "TowerDecorator.h"

// Upgrades a tower by increasing its range
class RangeDecorator : public TowerDecorator {
public:
    RangeDecorator(std::unique_ptr<Tower> tower)
        : TowerDecorator(std::move(tower)) {
    }

    int getRange() const override {
        return wrappedTower->getRange();
    }

    int upgrade() override {
        wrappedTower->setRange(wrappedTower->getRange() + 1); 
        return wrappedTower->upgrade();
    }

    void shoot(std::vector<std::unique_ptr<Critter>>& target, float currentTime) override {
        wrappedTower->shoot(target, currentTime);  

        if (wrappedTower->bullet) {
            this->bullet = std::move(wrappedTower->bullet);
        }
    }
};

#endif
