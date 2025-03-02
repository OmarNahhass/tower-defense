#pragma once
#ifndef CRITTEROBSERVER_H
#define CRITTEROBSERVER_H
#include <SFML/Graphics.hpp>

class Critter;

class CritterObserver {
public:
    sf::RenderWindow& window;
    virtual ~CritterObserver() = default;
    CritterObserver(sf::RenderWindow& window) : window(window) {};
    virtual void onCritterAdded(Critter& critter, sf::Texture& texture) = 0;
    virtual void onCritterMoved(Critter& critter, sf::Vector2f velocity) = 0;
};

#endif