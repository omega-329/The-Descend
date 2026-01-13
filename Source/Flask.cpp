#include "../Header/Flask.h"
flasks::flasks(float dmg, float hpAdd, float armorAdd,const std::string& nume,const std::string& descriere)
    :  Item(descriere, nume), dmg(dmg), hpAdd(hpAdd), armorAdd(armorAdd)
{
};
float flasks::interact()
{
    if (dmg != 0)
        return dmg;
    else if (hpAdd != 0)
        return hpAdd;
    else if (armorAdd != 0)
        return armorAdd;
    else
        return 0;
}
