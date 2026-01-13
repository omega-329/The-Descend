
#include "../Header/Armor.h"
armor:: armor(float dmgred,const std::string& nume,const std::string& descriere) : Item(descriere, nume), dmgRed(dmgred){};
[[nodiscard]] bool armor::getArmor() const
{
    return inInv;
}
void armor::setArmor()
{
    inInv=true;
}
[[nodiscard]] bool armor::getEquiped () const
{
    return isEquiped;
}
void armor::setEquiped()
{
    isEquiped=!isEquiped;
}
float armor::interact ()
{
    return dmgRed;
}