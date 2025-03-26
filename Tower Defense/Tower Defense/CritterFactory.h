#ifndef CRITTERFACTORY_H
#define CRITTERFACTORY_H

#include "Critter.h"
#include "FastCritter.h"
#include "StrongCritter.h"
#include "BossCritter.h"

#include <SFML/Graphics.hpp>
#include <memory>

class CritterFactory
{
public:
    virtual ~CritterFactory() = default;
    virtual std::unique_ptr<Critter> createCritter(int waveNumber, sf::Texture& texture) = 0;
};

class NormalCritterFactory : public CritterFactory
{
public:
    std::unique_ptr<Critter> createCritter(int waveNumber, sf::Texture& texture) override {
        return std::make_unique<Critter>(waveNumber, texture);  // Assumes Critter class has this constructor
    }
};

class FastCritterFactory : public CritterFactory
{
public:
    std::unique_ptr<Critter> createCritter(int waveNumber, sf::Texture& texture) override {
        return std::make_unique<FastCritter>(waveNumber, texture);
    }
};

class StrongCritterFactory : public CritterFactory
{
public:
    std::unique_ptr<Critter> createCritter(int waveNumber, sf::Texture& texture) override {
        return std::make_unique<StrongCritter>(waveNumber, texture);
    }
};

class BossCritterFactory : public CritterFactory
{
public:
    std::unique_ptr<Critter> createCritter(int waveNumber, sf::Texture& texture) override {
        return std::make_unique<BossCritter>(waveNumber, texture);
    }
};

#endif