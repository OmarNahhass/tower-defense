#include "CritterFactoryManager.h"

std::unique_ptr<CritterFactory> CritterFactoryManager::getFactoryForWave(int waveNumber)
{
    if (waveNumber % 5 == 0)
    {
        return std::make_unique<BossCritterFactory>();
    }
    else if (waveNumber > 10 && waveNumber % 4 == 0)
    {
        return std::make_unique<StrongCritterFactory>();
    }
    else if (waveNumber > 5 && waveNumber % 3 == 0)
    {
        return std::make_unique<FastCritterFactory>();
    }
    else
    {
        return std::make_unique<NormalCritterFactory>();
    }
}
