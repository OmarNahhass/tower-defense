#include "CritterView.h"
#include "Critter.h"
#include "Map.h"
#include "Menu.h"
#include "Tower.h"

void CritterView::onCritterMoved(Critter& critter, sf::Vector2f velocity) {
	critter.getSprite().move(velocity);
    this->drawCritters(critter);
}

void CritterView::onCritterAdded(Critter& critter, sf::Texture& texture) {
    
    critter.getSprite().setTexture(texture);

    // Ensure the sprite size matches the grid cell size
    critter.getSprite().setScale(cellSize / critter.getSprite().getTexture()->getSize().x,
        cellSize / critter.getSprite().getTexture()->getSize().y);

    critter.getSprite().setPosition(pathCells[0].x * cellSize, pathCells[0].y * cellSize); // Start at path's beginning

}

void CritterView::drawCritters(Critter& critter) {
    sf::Sprite critterSprite = critter.sprite;

    critterSprite.setScale(
        static_cast<float>(cellSize) / critterSprite.getTexture()->getSize().x,
        static_cast<float>(cellSize) / critterSprite.getTexture()->getSize().y
    );

   

    // Health bar properties
    float healthBarWidth = critterSprite.getGlobalBounds().width;
    float healthBarHeight = 5;

    // compute the remaining health 
    float healthPercentage = static_cast<float>(critter.getHitPoints()) / critter.getMaxHealth();

    // Background bar (Black)
    sf::RectangleShape healthBarBackground(sf::Vector2f(healthBarWidth, healthBarHeight));
    healthBarBackground.setFillColor(sf::Color::Black);
    healthBarBackground.setPosition(critterSprite.getPosition().x, critterSprite.getPosition().y - 10);

    // Remaining Health (Red, scales with health)
    sf::RectangleShape remainingHealth(sf::Vector2f(healthBarWidth * healthPercentage, healthBarHeight));
    remainingHealth.setFillColor(sf::Color::Red);
    remainingHealth.setPosition(healthBarBackground.getPosition());


    window.draw(critterSprite);
    window.draw(healthBarBackground);
    window.draw(remainingHealth);
}