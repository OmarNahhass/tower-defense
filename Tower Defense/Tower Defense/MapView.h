#pragma once
#ifndef MAP_VIEW_H
#define MAP_VIEW_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "MapObserver.h"
#include <vector>
#include "Map.h"

class MapView : public MapObserver {
public:
    float currentTime;

    int towerCount = 0;
    int playerCoins = 100;


    MapView(sf::RenderWindow& window) : MapObserver(window) {
        if (!grassTextureMap.loadFromFile("grass.png")) {
            std::cerr << "Error loading grass texture\n";
        }
        if (!pathTextureMap.loadFromFile("path.png")) {
            std::cerr << "Error loading path texture\n";
        }
        if (!towerTextureMap.loadFromFile("tower.png")) {
            std::cerr << "Error loading tower texture\n";
        }
    }

    void drawTowerCount(sf::RenderWindow& window);
    void drawCoinsCount(sf::RenderWindow& window);
    void onCellChanged(int x, int y, int newState);
    void drawSingleCell(sf::RenderWindow& window, int x, int y, int newState, int cellSize);


private:
    sf::Texture grassTextureMap, pathTextureMap, towerTextureMap;
};


#endif

