
#ifndef OOP_ARMOR_H
#define OOP_ARMOR_H

#include "Item.h"
class armor : public Item
{
protected:
    bool inInv=false, isEquiped=false;
    float dmgRed=0;
public:
    armor() = default;
    armor(float dmgred,const std::string& nume,const std::string& descriere);
    [[nodiscard]] bool getArmor () const;
    void setArmor();
    [[nodiscard]] bool getEquiped() const;
    void setEquiped();
    float interact () override;
};

#endif //OOP_ARMOR_H