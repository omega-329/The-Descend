//
// Created by omega on 06.12.2025.
//

#ifndef OOP_FLASKS_H
#define OOP_FLASKS_H

#include "Items.h"

class flasks : public Items
{
protected:
    int nrflask=0;
    float dmg=0, hpadd=33, armoradd=0;
public:
    flasks()=default;
    flasks(float dmg, float hpadd, float armoradd,const std::string& nume,const std::string& descriere);
    float interact () override;
};
#endif //OOP_FLASKS_H