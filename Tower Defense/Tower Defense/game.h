#pragma once

#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>

void displayGame(sf::RenderWindow& window);      // Opens SFML window and allows user interaction

extern int cellSize;

extern int numberOfCrittersPerWave;
extern int numberOfCrittersRemaining;

#endif