#pragma once
#ifndef ATKSPEEDDECORATOR_H
#define ATKSPEEDDECORATOR_H

#include "TowerDecorator.h"

// Upgrades a tower by increasing its rate of fire
class AtkSpeedDecorator : public TowerDecorator {
public:
    AtkSpeedDecorator(std::unique_ptr<Tower> tower)
        : TowerDecorator(std::move(tower)) {
    }

    float getFireRate() const override {
        return wrappedTower->getFireRate();
    }

    void upgrade() override {
        wrappedTower->upgrade();
        wrappedTower->setRateOfFire(wrappedTower->getFireRate() * 1.1f);
    }

    void shoot(std::vector<Critter>& target, float currentTime) override {
        wrappedTower->shoot(target, currentTime);
    }
};

#endif 