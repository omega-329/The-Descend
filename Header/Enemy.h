//
// Created by omega on 06.12.2025.
//

#ifndef OOP_ENEMIES_H
#define OOP_ENEMIES_H

#pragma once
#include "Entity.h"

class Enemies : public Entity
{
public:
    using Entity::Entity;
    void setTexture(const sf::Texture& texture);
    void setPosition(float x, float y);
    void hitIndicator();
    void resetIndicator();
    void draw(sf::RenderWindow& window) const;

};

#endif //OOP_ENEMIES_H