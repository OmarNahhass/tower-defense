#pragma once

#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>
#include "MapObserver.h"



extern std::vector<MapObserver*> observersMap;


// Observer methods
void addObserver(MapObserver* observer);
void removeObserver(MapObserver* observer);
void notifyObservers(int x, int y, int newState);

void handleMouseClick(sf::Vector2i mousePos, sf::Mouse::Button button, int cellSize);
void initializeMap();
void displayMap();
	

bool isValidMap();
void extractPath();

void startGame();


constexpr int ROWS = 20;
constexpr int COLS = 20;

extern int numberOfTowers;

extern int playerCoins;

constexpr int WINDOWSIZE = 800;

extern int grid[ROWS][COLS];  // Declare grid here but define in map.cpp

extern std::vector<sf::Vector2i> pathCells; // Stores path coordinates


#endif
