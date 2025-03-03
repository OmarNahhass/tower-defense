#pragma once
#ifndef MAPOBSERVER_H
#define MAPOBSERVER_H
#include <SFML/Graphics.hpp>

class Map;

class MapObserver {
public:
    sf::RenderWindow& window;
    virtual ~MapObserver() = default;
    MapObserver(sf::RenderWindow& window) : window(window) {};
    
    void displayInvalidMapScreen(std::string errorMessage);
    void handleMouseClick(sf::Vector2i mousePos, sf::Mouse::Button button, int cellSize);
    void extractPath();
};

#endif