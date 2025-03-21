#pragma once
#ifndef POWERDECORATOR_H
#define POWERDECORATOR_H

#include "TowerDecorator.h"

// Upgrades a tower by increasing its power
class PowerDecorator : public TowerDecorator {
public:
    PowerDecorator(std::unique_ptr<Tower> tower)
        : TowerDecorator(std::move(tower)) {
        power += 2;
    }

    void upgrade() override {
        wrappedTower->upgrade();
        power += 2;
    }


};

#endif 

