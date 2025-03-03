#pragma once
#ifndef MAP_VIEW_H
#define MAP_VIEW_H

#include <SFML/Graphics.hpp>
#include "MapObserver.h"
#include <vector>
#include "Map.h"

class MapView : public MapObserver {
public:
    float currentTime;
    MapView(sf::RenderWindow& window) : MapObserver(window) {}

    void onCellChanged(int x, int y, int newState);
    void updateGraphics(int x, int y, int newState);
};


#endif

