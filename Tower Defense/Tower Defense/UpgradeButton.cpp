#include "UpgradeButton.h"

// Define the static font outside the class
sf::Font UpgradeButton::font;

UpgradeButton::UpgradeButton(float x, float y, float width, float height, const std::string& label) {

    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Failed to load font!" << std::endl;
        return;
    }


    button.setSize(sf::Vector2f(width, height));
    button.setPosition(x, y);
    button.setFillColor(sf::Color(23, 181, 5));

    text.setFont(font);
    text.setString(label);
    text.setCharacterSize(15);
    text.setFillColor(sf::Color::White);
    text.setPosition(x + 10, y + 5);
}

void UpgradeButton::draw(sf::RenderWindow& window) {
    window.draw(button);
    window.draw(text);
}

bool UpgradeButton::isClicked(sf::Vector2f mousePos) {
    return button.getGlobalBounds().contains(mousePos);
}
