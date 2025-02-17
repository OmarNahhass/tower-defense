#pragma once

#ifndef CRITTER_H
#define CRITTER_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>

class Critter {

private:
    float lastHitTime = -2.0f;

public:
    int hitPoints, reward, strength, speed, level;
    bool reachedExit;

    const sf::Sprite& getSprite() const { return sprite; }

    float hitTime;  // Initialize hit time
    float hitDuration;  // Red border stays for 0.2s

    sf::Vector2f getPosition() const;

    sf::Sprite sprite;  // Visual representation
    int pathIndex;      // Tracks movement along the path
    float moveProgress; // Fraction of movement between two points

    Critter(int lvl, sf::Texture& texture);
    bool takeDamage(int damage, float currentTime);

    void setHitTime(float time) { lastHitTime = time; }
    bool isHit(float currentTime) const;

    void move(float deltaTime); // Movement logic
};

#endif
