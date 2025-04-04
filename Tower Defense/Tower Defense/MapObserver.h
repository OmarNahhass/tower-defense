#pragma once
#ifndef MAPOBSERVER_H
#define MAPOBSERVER_H

#include <SFML/Graphics.hpp>

class MapObserver {
public:
    sf::RenderWindow& window;
    virtual ~MapObserver() = default;
    MapObserver(sf::RenderWindow& window) : window(window) {};
    virtual void onCellChanged(int x, int y, int newState, int previousState) = 0;
    virtual void displayInvalidMapMessage(std::string message) = 0;
    //virtual void drawSingleCell(sf::RenderWindow& window, int x, int y, int newState, int cellSize);
};

#endif // MAPOBSERVER_H
