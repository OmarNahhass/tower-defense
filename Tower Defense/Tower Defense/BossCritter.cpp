#include "BossCritter.h"

BossCritter::BossCritter(int waveNumber, sf::Texture& texture) : Critter(waveNumber, texture)
{
    this->speed *= 0.5f;   // Very slow
    this->hitPoints *= 3.0f;  // Very tanky
}