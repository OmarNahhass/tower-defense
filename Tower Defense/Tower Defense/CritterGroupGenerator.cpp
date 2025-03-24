#include "CritterFactory.h"
#include "CritterGroupGenerator.h"

std::vector<std::unique_ptr<Critter>> CritterGroupGenerator::generateWaveCritters(int waveNumber, sf::Texture& texture, CritterObserver& observer)
{
    std::vector<std::unique_ptr<Critter>> wave;
    int numCritters = 5;
    wave.reserve(5); // Reserve memory to avoid reallocation

    for (int i = 0; i < numCritters; i++)
    {
        std::unique_ptr<CritterFactory> factory = CritterFactoryManager::getFactoryForWave(waveNumber);

        std::unique_ptr<Critter> critter = factory->createCritter(waveNumber, texture);

        critter->addObserver(&observer, texture);

        wave.push_back(std::move(critter));
    }

    return wave;
}
