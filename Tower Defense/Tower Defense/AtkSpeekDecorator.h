#pragma once
#ifndef ATKSPEEDDECORATOR_H
#define ATKSPEEDDECORATOR_H

#include "TowerDecorator.h"

// Upgrades a tower by increasing its rate of fire
class AtkSpeedDecorator : public TowerDecorator {
public:
    AtkSpeedDecorator(std::unique_ptr<Tower> tower)
        : TowerDecorator(std::move(tower)) {
            rateOfFire *= 1.1f;
    }

    void upgrade() override {
        wrappedTower->upgrade();
        rateOfFire *= 1.1f;
    }
};

#endif 