
#include "../Header/Armor.h"
armor:: armor(float dmgred,const std::string& nume,const std::string& descriere) : Item(descriere, nume), dmgred(dmgred){};
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
    isequiped=!isequiped;
}
float armor::interact ()
{
    return dmgred;
}