#pragma once
#ifndef RANGEDECORATOR_H
#define RANGEDECORATOR_H

#include "TowerDecorator.h"

// Upgrades a tower by increasing its range
class RangeDecorator : public TowerDecorator {
public:
    RangeDecorator(std::unique_ptr<Tower> tower)
        : TowerDecorator(std::move(tower)) {
        range++;
    }

    void upgrade() override {
        wrappedTower->upgrade();
        range++;
    }
};

#endif
