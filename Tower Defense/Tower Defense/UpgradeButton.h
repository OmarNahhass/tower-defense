#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class UpgradeButton {
private:
    sf::RectangleShape button;
    sf::Text text;
    static sf::Font font;  // Declare static font (no definition here!)

public:
    UpgradeButton(float x, float y, float width, float height, const std::string& label);

    void draw(sf::RenderWindow& window);
    bool isClicked(sf::Vector2f mousePos);
};
