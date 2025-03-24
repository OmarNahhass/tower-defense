#include "CritterFactory.h"
#include <cstdlib> 


std::unique_ptr<Critter> FastCritterFactory::createCritter(int waveNumber, sf::Texture& texture) {
    return std::make_unique<FastCritter>(waveNumber, texture);
}

std::unique_ptr<Critter> StrongCritterFactory::createCritter(int waveNumber, sf::Texture& texture) {
    return std::make_unique<StrongCritter>(waveNumber, texture);
}

std::unique_ptr<Critter> BossCritterFactory::createCritter(int waveNumber, sf::Texture& texture) {
    return std::make_unique<BossCritter>(waveNumber, texture);
}

std::unique_ptr<CritterFactory> CritterFactoryManager::getFactoryForWave(int waveNumber)
{
    // for some rounds, critters will be either much faster, stronger... or both
    if (waveNumber % 5 == 0)                                            
    {
        return std::make_unique<BossCritter>(texture, waveNumber);
    }
    else if (waveNumber > 10 && waveNumber % 4 == 0)
    {
        return std::make_unique<StrongCritter>(texture, waveNumber);
    }
    else if (waveNumber > 5 && waveNumber % 3 == 0)
    {
        return std::make_unique<FastCritter>(texture, waveNumber);
    }
    // a regular round with normal critters
    else
    {
        return std::make_unique<Critter>(texture, waveNumber);
    }
}