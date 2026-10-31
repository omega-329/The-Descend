//
// Created by omega on 10.01.2026.
//

#ifndef OOP_ENTITY_H
#define OOP_ENTITY_H

#pragma once
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Limb.h"

class Entity
{
protected:
    std::string name;
    std::string description;
    bool alive = true;
    bool unlocked = false;
    std::vector<Limb> limbs;
    sf::Sprite sprite;

public:
    Entity() = default;
    Entity(std::string name, std::string description, std::vector<Limb> limbs, const sf::Texture& texture);
    Entity(std::string name, std::string description, std::vector<Limb> limbs);
    [[nodiscard]] bool isAlive() const;
    void Kill();
    [[nodiscard]] bool isUnlocked() const;
    void Unlock();
    int getLimbCount() const;
    Limb& getLimb(int i);
    const Limb& getLimb(int i) const;
    const std::vector<Limb>& getLimbs() const{ return limbs; };
    const std::string& getName() const;
    const std::string& getDescription() const;
};

#endif //OOP_ENTITY_H