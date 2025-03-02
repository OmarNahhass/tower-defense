#pragma once

#ifndef CRITTER_H
#define CRITTER_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include "CritterObserver.h"


class Critter {

private:
    float lastHitTime = -2.0f;
    std::vector<CritterObserver*> observers;

public:
    // lvl = wave number
    Critter(int lvl, sf::Texture& texture);
    //Observer methods
    void addObserver(CritterObserver* observer, sf::Texture& texture);
    void removeObserver(CritterObserver* observer);
    void notifyMoved(sf::Vector2f velocity);
    void notifyRemoved();
    void notifyAdded(sf::Texture& texture);

    int hitPoints, reward, strength, speed, level;
    bool reachedExit;

    const sf::Sprite& getSprite() const { return sprite; }
    sf::Sprite& getSprite() { return sprite; }

    float hitTime;  // Initialize hit time
    float hitDuration;  // Red border stays for 0.2s

    sf::Vector2f getPosition() const;

    sf::Sprite sprite;  // Visual representation
    int pathIndex;      // Tracks movement along the path
    float moveProgress; // Fraction of movement between two points

    void displayGameOverScren();

    bool takeDamage(int damage, float currentTime);

    void setHitTime(float time) { lastHitTime = time; }
    bool isHit(float currentTime) const;

    void move(float deltaTime); // Movement logic
};

#endif
