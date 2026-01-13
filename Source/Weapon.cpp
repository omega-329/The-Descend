#include "../Header/Weapon.h"
weapons::weapons(float dmg, float miss, const std::string& descriere, const std::string& nume)
    : Item(descriere, nume), dmg(dmg), miss(miss)
{
}
[[nodiscard]] bool weapons::getWeapon() const
{
    return inInv;
}
void weapons::setWeapon()
{
    inInv=true;
}
[[nodiscard]] bool weapons::getEquip () const
{
    return isEquiped;
}
void weapons::setEquip()
{
    isEquiped=!isEquiped;
}
float weapons::interact()
{
    return dmg;
}