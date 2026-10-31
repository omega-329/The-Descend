#include"../Header/Limb.h"
Limb::Limb(std::string name, float MaxHP, float hp, float dmg)
{
    this->name = name;
    this->MaxHP = MaxHP;
    this->DMG = dmg;
    if (hp < 0) hp = 0;
    if (hp > MaxHP) hp = MaxHP;
    this->HP = hp;
}
[[nodiscard]] bool Limb::getIntact() const
{
    return isIntact;
}
void Limb::setSevered()
{
    isIntact = false;
}
[[nodiscard]] float Limb::getMaxHP() const
{
    return MaxHP;
}
[[nodiscard]] float Limb::getHP() const
{
    return HP;
}
void Limb::setHP(float new_hp)
{
    HP = new_hp;
    if (HP > MaxHP) HP = MaxHP;
    if (HP <= 0) isIntact = false;
}
[[nodiscard]] float Limb::getDMG() const
{
    return DMG;
}
std::string Limb::getName() const
{
    return name;
}