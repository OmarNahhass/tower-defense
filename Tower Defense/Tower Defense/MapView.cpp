#include "MapView.h"
#include "Map.h"

#include <iostream>


void MapView::onCellChanged(int x, int y, int newState) {
    std::cout << "Cell (" << x << ", " << y << ") changed to state " << newState << "\n";
    updateGraphics(x, y, newState);
}

void MapView::updateGraphics(int x, int y, int newState) {
    // Use SFML to update the cell's sprite based on newState
    sf::Color color;
    if (newState == 0) color = sf::Color::Green;  // Grass
    else if (newState == 1) color = sf::Color::Yellow;  // Path
    else if (newState == 2) color = sf::Color::Red;  // Tower


    //grid[x][y].setFillColor(color);
}
