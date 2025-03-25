#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>

#include "Game.h"
#include "Critter.h"

class Bullet {
public:
    sf::CircleShape shape;
    sf::Vector2f velocity;
    static constexpr float BULLET_SPEED = 0.02f;  // Constant bullet speed

    Bullet(sf::Vector2f startPosition, sf::Vector2f targetPosition)
        : position(startPosition), target(targetPosition) {

        shape.setRadius(5.0f);
        shape.setFillColor(sf::Color::Red);
        shape.setPosition(startPosition);

        // Compute direction
        sf::Vector2f direction = target - startPosition;
        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        if (length != 0) direction /= length;  

        // Scale velocity by BULLET_SPEED
        velocity = direction * BULLET_SPEED;
    }

    virtual void move(float deltaTime) = 0;  // Pure virtual, to be implemented by derived classes
    virtual void dealDamage(std::vector<std::unique_ptr<Critter>>& critters) = 0;  // Virtual damage logic

    bool hasReachedTarget() const {
        // Calculate distance between current position and target
        float distSquared = (position.x - target.x) * (position.x - target.x) +
            (position.y - target.y) * (position.y - target.y);

        // acceptable range for the bullet to reach the critter (bullet doesn't have to hit the exact coordinates of the target)
        float tolerance = 10.0f;
        float toleranceSquared = tolerance * tolerance;

        return distSquared <= toleranceSquared;
    }

    virtual bool shouldBulletBeRemoved() const {
        return false;  // Default is not removed
    }

    sf::Vector2f getPosition() const { return position; }

protected:
    sf::Vector2f position;
    sf::Vector2f target;
};


class DirectDamageBullet : public Bullet {
public:
    DirectDamageBullet(sf::Vector2f startPosition, sf::Vector2f targetPosition)
        : Bullet(startPosition, targetPosition) {
    }

    void move(float deltaTime) override {
        position += velocity * deltaTime;
        shape.setPosition(position);

        if (!hasDamagedTarget) {
            dealDamage(activeCritters);
        }
    }

    void dealDamage(std::vector<std::unique_ptr<Critter>>& critters) override {
        // Deal damage if the bullet has reached the target
        for (auto& critter : critters) {
            if (hasReachedTarget()) {
                std::cout << "Critter shot!";
                critter->takeDamage(2, 0);  
                hasDamagedTarget = true;
                break;
            }
        }
    }

    bool shouldBulletBeRemoved() const override {
        return hasDamagedTarget;
    }

private:
    bool hasDamagedTarget = false;
};


class SlowingBullet : public Bullet {
public:
    SlowingBullet(sf::Vector2f startPosition, sf::Vector2f targetPosition)
        : Bullet(startPosition, targetPosition) {
    }

    void move(float deltaTime) override {
        // Move the bullet directly towards the target
        sf::Vector2f direction = target - position;
        float magnitude = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        direction /= magnitude;  // Normalize direction vector

        position += direction * BULLET_SPEED * deltaTime;
    }

    void dealDamage(std::vector<std::unique_ptr<Critter>>& critters) override {
        // Deal damage if the bullet has reached the target
        for (auto& critter : critters) {
            if (hasReachedTarget()) {
                critter->takeDamage(0, 0);  
                break;  // Only damage one critter for now
            }
        }
    }
};



class SniperBullet : public Bullet {
public:
    SniperBullet(sf::Vector2f startPosition, sf::Vector2f targetPosition)
        : Bullet(startPosition, targetPosition) {
    }

    void move(float deltaTime) override {
        // Move the bullet directly towards the target
        sf::Vector2f direction = target - position;
        float magnitude = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        direction /= magnitude;  // Normalize direction vector

        position += direction * BULLET_SPEED * deltaTime;
    }

    void dealDamage(std::vector<std::unique_ptr<Critter>>& critters) override {
        // Deal damage if the bullet has reached the target
        for (auto& critter : critters) {
            if (hasReachedTarget()) {
                critter->takeDamage(10, 0);  
                break;  // Only damage one critter for now
            }
        }
    }
};