#ifndef CRITTERFACTORY_H
#define CRITTERFACTORY_H

#include "Critter.h"
#include <SFML/Graphics.hpp>
#include <memory>

class CritterFactory
{
public:
    virtual ~CritterFactory() = default;
    virtual std::unique_ptr<Critter> createCritter(int waveNumber, sf::Texture& texture) = 0;
};

class FastCritterFactory : public CritterFactory
{
public:
    std::unique_ptr<Critter> createCritter(int waveNumber, sf::Texture& texture) override;
};

class StrongCritterFactory : public CritterFactory
{
public:
    std::unique_ptr<Critter> createCritter(int waveNumber, sf::Texture& texture) override;
};

class BossCritterFactory : public CritterFactory
{
public:
    std::unique_ptr<Critter> createCritter(int waveNumber, sf::Texture& texture) override;
};

class CritterFactoryManager
{
public:
    static std::vector<std::unique_ptr<Critter>> generateWave(int waveNumber, sf::Texture& texture, CritterObserver& observer);

private:
    static std::unique_ptr<CritterFactory> getFactoryForWave(int waveNumber);
};

#endif