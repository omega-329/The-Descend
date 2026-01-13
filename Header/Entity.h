//
// Created by omega on 10.01.2026.
//

#ifndef OOP_ENTITY_H
#define OOP_ENTITY_H

#pragma once
#include <string>
#include <vector>
#include "Limb.h"

class Entity
{
protected:
    std::string name;
    std::string description;
    bool alive = true;
    std::vector<Limb> limbs;

public:
    Entity() = default;
    Entity(std::string name,
           std::string description,
           std::vector<Limb> limbs);

    [[nodiscard]] bool isAlive() const;
    void Kill();

    int getLimbCount() const;
    Limb& getLimb(int i);
    const Limb& getLimb(int i) const;
    const std::vector<Limb>& getLimbs() const{ return limbs; };

    const std::string& getName() const;
    const std::string& getDescription() const;
};

#endif //OOP_ENTITY_H