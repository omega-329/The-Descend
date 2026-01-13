#include"../Header/Limb.h"
Limb::Limb(std::string name, float hp, float dmg)
{
    this->name = name;
    this->HP = hp;
    this->DMG = dmg;
}
[[nodiscard]] bool Limb::getIntact() const
{
    return isIntact;
}
void Limb::setIntact()
{
    isIntact= false;
}
[[nodiscard]] float Limb::getHP() const
{
    return HP;
}
void Limb::setHP(float new_hp)
{
    HP=new_hp;
}
[[nodiscard]] float Limb::getDMG() const
{
    return DMG;
}
std::string Limb::getName() const
{
    return name;
}