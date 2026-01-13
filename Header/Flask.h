
#ifndef OOP_FLASKS_H
#define OOP_FLASKS_H

#include "Item.h"

class flasks : public Item
{
protected:
    int nrFlask=0;
    float dmg=0, hpAdd=40, armorAdd=0;
public:
    flasks()=default;
    flasks(float dmg, float hpAdd, float armorAdd,const std::string& nume,const std::string& descriere);
    float interact () override;
};
#endif //OOP_FLASKS_H