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
    virtual ~Critter() = default;

    int hitPoints, reward, strength, initialSpeed, speed, level;

    bool isSlowed;
    float slowEndTime;

    int maxHealth;

    bool reachedExit;

    float hitTime;  // Initialize hit time
    float hitDuration;  // Red border stays for 0.2s

    sf::Sprite sprite;  // Visual representation
    int pathIndex;      // Tracks movement along the path
    float moveProgress; // Fraction of movement between two points


    int getMaxHealth() {
        return maxHealth;
    }

    int getHitPoints() {
        return hitPoints;
    }

    const sf::Sprite& getSprite() const { return sprite; }
    sf::Sprite& getSprite() { return sprite; }

    virtual std::string getType() const { return "Basic Critter"; }

    sf::Vector2f getPosition() const;

    void displayGameOverScren();

    bool takeDamage(int damage, float currentTime);

    void slowDown(float currentTime);

    void setHitTime(float time) { lastHitTime = time; }
    bool isHit(float currentTime) const;

    void move(float deltaTime); // Movement logic

    int getRemainingPathCells();



    //Observer methods
    void addObserver(CritterObserver* observer, sf::Texture& texture);
    void removeObserver(CritterObserver* observer);
    void notifyMoved(sf::Vector2f velocity);
    void notifyRemoved();
    void notifyAdded(sf::Texture& texture);
};

#endif
