#pragma once
#ifndef POWERDECORATOR_H
#define POWERDECORATOR_H

#include "TowerDecorator.h"

// Increases a tower's power
class PowerDecorator : public TowerDecorator {
public:
    PowerDecorator(std::unique_ptr<Tower> tower)
        : TowerDecorator(std::move(tower)) {
    }

    int getPower() const override {
        return wrappedTower->getPower();  
    }

    void upgrade() override {
        wrappedTower->upgrade();  
        wrappedTower->setPower(wrappedTower->getPower() + 2);
    }

    void shoot(std::vector<Critter>& target, float currentTime) override {
        wrappedTower->shoot(target, currentTime);  
    }


};

#endif
