#include "CritterGroupGenerator.h"

std::vector<Critter> CritterGroupGenerator::generateWaveCritters(int waveNumber, sf::Texture& texture) {
    std::vector<Critter> crittersWave;
    crittersWave.reserve(10); // Reserve space to avoid reallocations

    // 10 critters per wave
    for (int i = 0; i < 10; i++) {
        crittersWave.emplace_back(waveNumber, texture);
    }

    return crittersWave;
}
