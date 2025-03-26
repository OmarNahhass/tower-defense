#ifndef BOSSCRITTER_H
#define BOSSCRITTER_H

#include "Critter.h"

class BossCritter : public Critter
{
public:
    BossCritter(int waveNumber, sf::Texture& texture);
    std::string getType() const override { return "Boss"; }
};

#endif