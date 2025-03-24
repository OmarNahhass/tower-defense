#include "FastCritter.h"

FastCritter::FastCritter(int waveNumber, sf::Texture& texture) : Critter(waveNumber, texture)
{
    this->speed *= 1.5f;      // Faster movement
    this->hitPoints *= 0.75f; // Less health
}
