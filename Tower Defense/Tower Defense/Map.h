#pragma once

#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>
#include "Menu.h"
#include "MapObserver.h"



extern std::vector<MapObserver*> observersMap;


// Observer methods
void addObserver(MapObserver* observer);
void removeObserver(MapObserver* observer);
void notifyObservers(int column, int row, int newState);

void handleMouseClick(sf::Vector2i mousePos, sf::Mouse::Button button, int cellSize);
void initializeMap(int numberOfRows, int numberOfColumns);

void drawFullMap(sf::RenderWindow& window, int cellSize);
void displayMap(int windowWidth, int windowHeight, int numberOfRows, int numberOfColumns);
	

bool isValidMap();
void extractPath();

void startGame();

extern int** mapGrid;

constexpr int ROWS = 20;
constexpr int COLS = 20;

extern int numberOfTowers;

constexpr int WINDOWSIZE = 800;

extern int grid[ROWS][COLS];  // Declare grid here but define in map.cpp

extern std::vector<sf::Vector2i> pathCells; // Stores path coordinates


#endif
