#include "../Header/Weapon.h"
weapons::weapons(float dmg, float miss, const std::string& descriere, const std::string& nume)
    : Item(descriere, nume), dmg(dmg), miss(miss)
{
}
[[nodiscard]] bool weapons::getweapon() const
{
    return ininv;
}
void weapons::setweapon()
{
    ininv=true;
}
[[nodiscard]] bool weapons::getequip () const
{
    return isequiped;
}
void weapons::setequip()
{
    isequiped=!isequiped;
}
float weapons::interact()
{
    return dmg;
}