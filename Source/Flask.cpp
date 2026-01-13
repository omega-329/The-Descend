#include "../Header/Flask.h"
flasks::flasks(float dmg, float hpadd, float armoradd,const std::string& nume,const std::string& descriere)
    :  Item(descriere, nume), dmg(dmg), hpadd(hpadd), armoradd(armoradd)
{
};
float flasks::interact()
{
    if (dmg != 0)
        return dmg;
    else if (hpadd != 0)
        return hpadd;
    else if (armoradd != 0)
        return armoradd;
    else
        return 0;
}
