
#ifndef OOP_FLASKS_H
#define OOP_FLASKS_H

#include "Item.h"

class flasks : public Item
{
protected:
    float dmg=0, hpAdd=40, armorAdd=0;
public:
    flasks()=default;
    flasks(float dmg, float hpAdd, float armorAdd,const std::string& nume,const std::string& descriere);
    float interact () override;
    [[nodiscard]] bool isConsumable() const override;
};
#endif //OOP_FLASKS_H