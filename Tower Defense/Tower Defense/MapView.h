#pragma once
#ifndef MAP_VIEW_H
#define MAP_VIEW_H

#include "MapObserver.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include "Map.h"

class MapView : public MapObserver {
public:
    float currentTime;
    MapView(sf::RenderWindow& window) : MapObserver(window) {}

    void displayInvalidMapScreen(std::string errorMessage);
    void handleMouseClick(sf::Vector2i mousePos, sf::Mouse::Button button, int cellSize);
    void extractPath();
private:
    std::vector<Map*> maps;

};


#endif

