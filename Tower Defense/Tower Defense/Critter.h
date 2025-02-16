#pragma once

#ifndef CRITTER_H
#define CRITTER_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>

class Critter {
public:
    int hitPoints, reward, strength, speed, level;
    bool reachedExit;

    sf::Sprite sprite;  // Visual representation
    int pathIndex;      // Tracks movement along the path
    float moveProgress; // Fraction of movement between two points

    Critter(int lvl, sf::Texture& texture);
    bool takeDamage(int damage);
    void move(float deltaTime); // Movement logic
};

#endif
