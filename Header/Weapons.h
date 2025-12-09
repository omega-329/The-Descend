//
// Created by omega on 06.12.2025.
//

#ifndef OOP_WEAPONS_H
#define OOP_WEAPONS_H

#include <string>
#include "Items.h"
class weapons : public Items
{
protected:
    bool ininv=false, isequiped=false;
    float dmg=50, miss=20;
public:
    weapons()=default;
    weapons(float dmg, float miss,const std::string& descriere,const std::string& nume);
    [[nodiscard]] bool getweapon () const;
    void setweapon();
    [[nodiscard]] bool getequip () const;
    void setequip();
    float interact() override;
};
#endif //OOP_WEAPONS_H