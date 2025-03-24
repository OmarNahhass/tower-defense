#ifndef CRITTERFACTORYMANAGER_H
#define CRITTERFACTORYMANAGER_H

#include "CritterFactory.h"

class CritterFactoryManager
{
public:
    static std::unique_ptr<CritterFactory> getFactoryForWave(int waveNumber);
};

#endif
