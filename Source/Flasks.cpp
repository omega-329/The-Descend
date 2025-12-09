#include "../Header/Flasks.h"
flasks::flasks(float dmg, float hpadd, float armoradd,const std::string& nume,const std::string& descriere)
{
    this->dmg = dmg;
    this->hpadd = hpadd;
    this->armoradd = armoradd;
    this->nume = nume;
    this->descriere = descriere;
}
float flasks::interact()
{
    if (dmg >= 0)
        return dmg;
    else if (hpadd >= 0)
        return hpadd;
    else if (armoradd >= 0)
        return armoradd;
}
