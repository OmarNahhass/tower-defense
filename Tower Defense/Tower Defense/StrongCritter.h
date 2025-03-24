#ifndef STRONGCRITTER_H
#define STRONGCRITTER_H

#include "Critter.h"

class StrongCritter : public Critter
{
public:
    StrongCritter(int waveNumber, sf::Texture& texture);
    std::string getType() const override { return "Strong"; }
};

#endif