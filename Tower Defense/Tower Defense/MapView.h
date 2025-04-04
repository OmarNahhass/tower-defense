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
        if (!towerSlowDownTextureMap.loadFromFile("towerSlowDown.png")) {
            std::cerr << "Error loading towerSlowDown texture\n";
        }
        if (!towerSniperTextureMap.loadFromFile("towerSniper.png")) {
            std::cerr << "Error loading towerSniper texture\n";
        }
    }

    void drawTowerCount(sf::RenderWindow& window);
    void drawCoinsCount(sf::RenderWindow& window);
    void onCellChanged(int x, int y, int newState, int previousState);
    void displayInvalidMapMessage(std::string message);
    void drawSingleCell(sf::RenderWindow& window, int x, int y, int newState, int cellSize);


private:
    sf::Texture grassTextureMap, pathTextureMap, towerTextureMap, towerSlowDownTextureMap, towerSniperTextureMap;
};


extern int towerCounter;
extern int playerCoins;
extern std::string invalidMapMessage;


#endif

