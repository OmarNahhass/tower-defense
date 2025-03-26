#ifndef FASTCRITTER_H
#define FASTCRITTER_H

#include "Critter.h"

class FastCritter : public Critter
{
public:
    FastCritter(int waveNumber, sf::Texture& texture);
    std::string getType() const override { return "Fast"; }
};

#endif
