#pragma once
#ifndef STRATEGIES_H
#define STRATEGIES_H

#include <vector>
#include "Critter.h"  


class Strategies {
public:
    virtual ~Strategies() = default; // Virtual destructor for proper cleanup

    virtual Critter* selectTarget(std::vector<Critter*>& targets) { return nullptr; }

    virtual Critter* selectTarget(std::vector<Critter*>& targets, int posX, int pos) { return nullptr; }

    virtual std::unique_ptr<Strategies> clone() const = 0;
};


class NearestToTower : public Strategies {
public:
    Critter* selectTarget(std::vector<Critter*>& targets, int postX, int posY) override;

    std::unique_ptr<Strategies> clone() const override {
        return std::make_unique<NearestToTower>(*this);
    }
};


class NearestToExit : public Strategies {
public:
    Critter* selectTarget(std::vector<Critter*>& targets, int posX, int posY) override;

    std::unique_ptr<Strategies> clone() const override {
        return std::make_unique<NearestToExit>(*this);
    }
};


class StrongestCritter : public Strategies {
public:
    Critter* selectTarget(std::vector<Critter*>& targets) override;

    std::unique_ptr<Strategies> clone() const override {
        return std::make_unique<StrongestCritter>(*this);
    }
};


class WeakestCritter : public Strategies {
public:
    Critter* selectTarget(std::vector<Critter*>& targets) override;

    std::unique_ptr<Strategies> clone() const override {
        return std::make_unique<WeakestCritter>(*this);
    }
};

#endif