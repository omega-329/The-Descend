//
// Created by omega on 06.12.2025.
//

#ifndef OOP_WEAPONS_H
#define OOP_WEAPONS_H

#include <string>
#include "Item.h"
class weapons : public Item
{
protected:
    bool inInv=false, isEquiped=false;
    float dmg=50, miss=20;
public:
    weapons()=default;
    weapons(float dmg, float miss,const std::string& descriere,const std::string& nume);
    [[nodiscard]] bool getWeapon () const;
    void setWeapon();
    [[nodiscard]] bool getEquip () const;
    void setEquip();
    float interact() override;
};
#endif //OOP_WEAPONS_H