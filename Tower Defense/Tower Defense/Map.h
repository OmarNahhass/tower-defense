#pragma once

#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>

constexpr int ROWS = 20;
constexpr int COLS = 20;

extern int grid[ROWS][COLS];  // Declare grid here but define in map.cpp

void initializeMap();
void displayMap();

bool isValidMap();

void handleMouseClick(sf::Vector2i mousePos, sf::Mouse::Button button, int cellSize);
void startGame();

#endif
