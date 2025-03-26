#pragma once
#ifndef CRITTER_VIEW_H
#define CRITTER_VIEW_H

#include "CritterObserver.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include "Map.h"

class CritterView: public CritterObserver {
public:
    float currentTime;
    CritterView(sf::RenderWindow& window) : CritterObserver(window) {}

    virtual ~CritterView() {
        // Properly remove observer when view is destroyed
        for (auto* critter : critters) {
            critter->removeObserver(this);
        }
    }

    void drawCritters(Critter& critter);
    void onCritterMoved(Critter& critter, sf::Vector2f velocity) override;
    void onCritterAdded(Critter& critter, sf::Texture& texture) override;
private:
    std::vector<Critter*> critters;
};
#endif