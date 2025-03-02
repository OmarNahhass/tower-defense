#ifndef CRITTERGROUPGENERATOR_H
#define CRITTERGROUPGENERATOR_H

#include <list>
#include "Critter.h"
#include <SFML/Graphics.hpp>

class CritterGroupGenerator {
public:
	static std::vector<Critter> generateWaveCritters(int waveNumber, sf::Texture& texture, CritterObserver& observer);
};

#endif


