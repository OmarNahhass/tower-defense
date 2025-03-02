#include "CritterGroupGenerator.h"
#include "Game.h"

std::vector<Critter> CritterGroupGenerator::generateWaveCritters(int waveNumber, sf::Texture& texture, CritterObserver& observer) {
    std::vector<Critter> crittersWave;
    crittersWave.reserve(10); // Reserve space to avoid reallocations

    // 10 critters per wave
    for (int i = 0; i < numberOfCrittersPerWave; i++) {
        crittersWave.emplace_back(waveNumber, texture);
        crittersWave.back().addObserver(&observer, texture);
    }

    return crittersWave;
}
