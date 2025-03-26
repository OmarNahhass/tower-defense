#include "StrongCritter.h"

StrongCritter::StrongCritter(int waveNumber, sf::Texture& texture) : Critter(waveNumber, texture)
{
    this->speed *= 0.75f;  // Slower movement
    this->hitPoints *= 1.5f;  // More health
}