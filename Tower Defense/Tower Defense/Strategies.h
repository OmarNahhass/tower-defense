#pragma once
#ifndef STRATEGIES_H
#define STRATEGIES_H

#include <vector>
#include "Critter.h"  

class Strategies {
public:
    virtual ~Strategies() = default; // Virtual destructor for proper cleanup
    virtual Critter* selectTarget(std::vector<Critter*>& targets) = 0;
};


class NearestToTower : public Strategies {
public:
    Critter* selectTarget(std::vector<Critter*>& targets) override;
};


class NearestToExit : public Strategies {
public:
    Critter* selectTarget(std::vector<Critter*>& targets) override;
};


class StrongestCritter : public Strategies {
public:
    Critter* selectTarget(std::vector<Critter*>& targets) override;
};


class WeakestCritter : public Strategies {
public:
    Critter* selectTarget(std::vector<Critter*>& targets) override;
};

#endif