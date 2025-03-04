#pragma once

#ifndef MENU_H
#define MENU_H


extern int numberOfRows;
extern int numberOfColumns;

extern int cellSize;

extern int windowWidth; 
extern int windowHeight;

extern int maxMapWidth;
extern int maxMapHeight;

extern int mapWidth;
extern int mapHeight;

extern int infoPanelWidth;
extern int infoPanelHeight;

void menuScreen();
void startMapEditor(int width, int height, int numCells);



#endif