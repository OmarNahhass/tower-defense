#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>

#include "Game.h"
#include "Game.h"
#include "Critter.h"

class Bullet {
public:
    sf::CircleShape shape;
    sf::Vector2f velocity;
    static constexpr float BULLET_SPEED = 0.03f;  // Constant bullet speed

    Bullet(sf::Vector2f startPosition, Critter* critter)
        : position(startPosition), target(critter) {

        shape.setRadius(5.0f);
        shape.setFillColor(sf::Color::Red);
        shape.setPosition(startPosition);

        targetPosition = { target->getPosition().x , target->getPosition().y};

        // Compute direction
        sf::Vector2f direction = targetPosition - position;
        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        if (length != 0) direction /= length;  

        // Scale velocity by BULLET_SPEED
        velocity = direction * BULLET_SPEED;
    }


    virtual void move(float deltaTime) = 0;  // Pure virtual, to be implemented by derived classes
    virtual void dealDamage() = 0;  // Virtual damage logic

    bool hasReachedTarget() const {
        // Calculate distance between current position and target
        float distSquared = (position.x - target->getPosition().x) * (position.x - target->getPosition().x) +
            (position.y - target->getPosition().y) * (position.y - target->getPosition().y);

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
    Critter* target;
    sf::Vector2f targetPosition;
};


class DirectDamageBullet : public Bullet {
public:
    DirectDamageBullet(sf::Vector2f startPosition, Critter* target)
        : Bullet(startPosition, target) {
    }

    void move(float deltaTime) override {
        // Recalculate direction to target every frame
        sf::Vector2f direction = targetPosition - position;
        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

        if (length > 0) {
            direction /= length; // Normalize
            velocity = direction * BULLET_SPEED; // Scale velocity
        }

        position += velocity * deltaTime;
        shape.setPosition(position);

        if (!hasDamagedTarget) {
            dealDamage();
        }
    }

    void dealDamage() override {
        // Deal damage if the bullet has reached the target
        if (hasReachedTarget()) {
            target->takeDamage(2, 0);  
            hasDamagedTarget = true;
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
    SlowingBullet(sf::Vector2f startPosition, Critter* target, float currentTime)
        : Bullet(startPosition, target) {

        currentTime = currentTime;
    }

    void move(float deltaTime) override {
        // Recalculate direction to target every frame
        sf::Vector2f direction = targetPosition - position;
        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

        if (length > 0) {
            direction /= length; // Normalize
            velocity = direction * BULLET_SPEED; // Scale velocity
        }

        position += velocity * deltaTime;
        shape.setPosition(position);

        if (!hasSlowedTheTarget) {
            dealDamage();
        }
    }

    void dealDamage() override {
        // Deal damage if the bullet has reached the target
        if (hasReachedTarget()) {
            target->slowDown(currentTime);  
            hasSlowedTheTarget = true;
        }
    }

    bool shouldBulletBeRemoved() const override {
        return hasSlowedTheTarget;
    }

private:
    float currentTime = 0.0f;
    bool hasSlowedTheTarget = false;
};



class SniperBullet : public Bullet {
public:
    SniperBullet(sf::Vector2f startPosition, Critter* target)
        : Bullet(startPosition, target) {
    }

    void move(float deltaTime) override {
        // Move the bullet directly towards the target
        sf::Vector2f direction = targetPosition - position;
        float magnitude = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        direction /= magnitude;  // Normalize direction vector

        position += direction * BULLET_SPEED * deltaTime;
    }

    void dealDamage() override {
        // Deal damage if the bullet has reached the target
        if (hasReachedTarget()) {
            target->takeDamage(10, 0);  
        }
    }
};