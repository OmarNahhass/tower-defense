#pragma once
#ifndef MAPOBSERVER_H
#define MAPOBSERVER_H

#include <SFML/Graphics.hpp>

class MapObserver {
public:
    sf::RenderWindow& window;
    virtual ~MapObserver() = default;
    MapObserver(sf::RenderWindow& window) : window(window) {};
    virtual void onCellChanged(int x, int y, int newState) = 0;
};

#endif // MAPOBSERVER_H
