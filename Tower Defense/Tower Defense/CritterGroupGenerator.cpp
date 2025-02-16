#include "CritterGroupGenerator.h"
class CritterGroupGenerator {
public:
	static std::list<Critter> generateWaveCritters(int waveNumber) {
		std::list<Critter> crittersWave;
		int minLevel = waveNumber; // The minimum level should increase with wave number
		//There should be 3 more critters with every wave
		for (int i = 0; i < waveNumber + 3; i++) { 
			int critterLevel = minLevel + (i % 3); //Making sure the level is not the same for all critters in the wave
			crittersWave.push_back(Critter(critterLevel));
		}
	}
};
