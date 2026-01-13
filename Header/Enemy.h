//
// Created by omega on 06.12.2025.
//

#ifndef OOP_ENEMIES_H
#define OOP_ENEMIES_H

#pragma once
#include "Entity.h"
#include <SFML/Graphics.hpp>

class Enemies : public Entity
{
private:
    bool unlocked = false;
    sf::Sprite sprite;
public:
    Enemies(std::string name, std::string description, std::vector<Limb> limbs);

    bool isUnlocked() const;
    void Unlock();

    void setTexture(const sf::Texture& texture);
    void setPosition(float x, float y);
    void hitIndicator();
    void resetIndicator();
    void draw(sf::RenderWindow& window) const;

};

#endif //OOP_ENEMIES_H