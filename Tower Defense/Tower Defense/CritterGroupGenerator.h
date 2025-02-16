#pragma once
#include <list>
#include "Critter.h"
class CritterGroupGenerator
{
public:
	static std::list<Critter> generateWaveCritters(int waveNumber);
};

