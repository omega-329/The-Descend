//
// Created by omega on 09.12.2025.
//

#ifndef OOP_PLAYERINVENTORY_H
#define OOP_PLAYERINVENTORY_H
#include <vector>
#include "../Header/Armor.h"
#include "../Header/Weapons.h"
#include "../Header/Flasks.h"
class PlayerInventory
{
    std::vector<weapons> weaponsList;
    std::vector<armor> armors;
    std::vector<flasks> flasks;

public:
    void addWeapon(const weapons& w);
    void removeWeapon(int index);
    weapons& getWeapon(int index);

    void addArmor(const armor& a);
    void removeArmor(int index);
    armor& getArmor(int index);

    void addFlask(const flasks& f);
    void removeFlask(int index);
    flasks& getFlask(int index);
};

#endif //OOP_PLAYERINVENTORY_H