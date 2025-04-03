#include <stdio.h>
#include "LogFile.h"
#include "Menu.h"
#include "Map.h"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#include <iostream>


int main() {
    initializeLogFile("game_log.txt");

    menuScreen();

    if (isValidMap())
        startGame();


    closeLog();

    return 0;
}
