#include "CritterGroupGenerator.h"

std::list<Critter> CritterGroupGenerator::generateWaveCritters(int waveNumber, sf::Texture& texture) {
    std::list<Critter> crittersWave;
    int minLevel = waveNumber;

    for (int i = 0; i < waveNumber + 3; i++) {
        int critterLevel = minLevel + (i % 3); // Varied levels
        crittersWave.emplace_back(critterLevel, texture); // Pass texture to Critter
    }

    return crittersWave;
}
