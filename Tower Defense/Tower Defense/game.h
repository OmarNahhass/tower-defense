#pragma once

#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>

void displayGame(sf::RenderWindow& window);      // Opens SFML window and allows user interaction

enum class GameState {
    InGame,            // Game is running
    WaveStart,
    WaveEnd,           // Wave has ended and waiting for the next wave
    MapCustomization,  // Map customization phase before starting the next wave
};

extern GameState currentState;

extern int numberOfCrittersPerWave;
extern int numberOfCrittersRemaining;


#endif