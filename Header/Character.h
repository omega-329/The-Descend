//
// Created by omega on 06.12.2025.
//

#ifndef OOP_CHARACTER_H
#define OOP_CHARACTER_H

#pragma once
#include "Entity.h"
#include "Weapon.h"
#include "Armor.h"

class Character : public Entity
{
private:
    weapons currentWeapon;
    armor currentArmor;
    bool guard;

public:
    using Entity::Entity;

    void equipWeapon(const weapons& w);
    void equipArmor(const armor& a);

    void setGuarding(bool val);
    bool getGuarding() const;

    weapons& getWeapon();
    [[nodiscard]] const armor& getArmor() const;
};
#endif //OOP_CHARACTER_H