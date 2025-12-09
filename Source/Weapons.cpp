#include "../Header/Weapons.h"
weapons::weapons(float dmg, float miss,const std::string& descriere,const std::string& nume)
{
    this->dmg=dmg;
    this->miss=miss;
    this->descriere=descriere;
    this->nume=nume;
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
    isequiped=true;
}
float weapons::interact()
{
    return dmg;
}