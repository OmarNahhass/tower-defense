#include "CritterView.h"
#include "Critter.h"

void CritterView::onCritterMoved(Critter& critter, sf::Vector2f velocity) {
	critter.getSprite().move(velocity);
    this->drawCritters(critter);
}

void CritterView::onCritterAdded(Critter& critter, sf::Texture& texture) {
    
    critter.getSprite().setTexture(texture);

    // Ensure the sprite size matches the grid cell size
    float cellSize = static_cast<float>(WINDOWSIZE) / ROWS;
    critter.getSprite().setScale(cellSize / critter.getSprite().getTexture()->getSize().x,
        cellSize / critter.getSprite().getTexture()->getSize().y);

    critter.getSprite().setPosition(pathCells[0].x * cellSize, pathCells[0].y * cellSize); // Start at path's beginning

}

void CritterView::drawCritters(Critter& critter) {
    sf::Sprite critterSprite = critter.sprite;

    //critterSprite.setPosition(critter.position.x * cellSize, critter.position.y * cellSize);

    critterSprite.setScale(
        static_cast<float>(WINDOWSIZE / ROWS) / critterSprite.getTexture()->getSize().x,
        static_cast<float>(WINDOWSIZE / ROWS) / critterSprite.getTexture()->getSize().y
    );

    window.draw(critterSprite);

    if (critter.isHit(currentTime)) {  // Draw red border if recently hit
        sf::RectangleShape border(sf::Vector2f(critterSprite.getGlobalBounds().width, critterSprite.getGlobalBounds().height));

        // Red border for when a critter gets hit
        border.setPosition(critterSprite.getGlobalBounds().left, critterSprite.getGlobalBounds().top);
        border.setOutlineThickness(3);
        border.setOutlineColor(sf::Color::Red);
        border.setFillColor(sf::Color::Transparent);

        window.draw(border);
    }
}