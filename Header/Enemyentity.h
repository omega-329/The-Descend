//
// Created by omega on 06.01.2026.
//

#ifndef OOP_ENEMYENTITY_H
#define OOP_ENEMYENTITY_H

#pragma once
#include <SFML/Graphics.hpp>
#include "Enemy.h"

class EnemyEntity
{
private:
    Enemies enemy;
    sf::Sprite sprite;
public:
    EnemyEntity(Enemies enemy,
                const sf::Texture& texture,
                sf::Vector2f position);

    void update(float dt);
    void draw(sf::RenderWindow& window);
    sf::FloatRect getBounds() const;

    Enemies& getEnemy();
};

#endif //OOP_ENEMYENTITY_H