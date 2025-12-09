//
// Created by omega on 09.12.2025.
//
#include "../Header/Armor.h"
armor::armor(float dmgred) : dmgred(dmgred) {}
[[nodiscard]] bool armor::getarmor() const
{
    return ininv;
}
void armor::setarmor()
{
    ininv=true;
}
[[nodiscard]] bool armor::getequiped () const
{
    return isequiped;
}
void armor::setequiped()
{
    isequiped=true;
}
float armor::interact ()
{
    return dmgred;
}