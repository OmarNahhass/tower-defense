#ifndef CRITTERGROUPGENERATOR_H
#define CRITTERGROUPGENERATOR_H

#include <list>
#include "Critter.h"
#include <SFML/Graphics.hpp>

class CritterGroupGenerator {
public:
	static std::vector<std::unique_ptr<Critter>> generateWaveCritters(int waveNumber, sf::Texture& texture, CritterObserver& observer);
};

#endif


