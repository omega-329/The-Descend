#include"../Header/Limb.h"
limb::limb(float hp, float dmg)
{
    this->hp=hp;
    this->dmg=dmg;
};
[[nodiscard]] bool limb::getintact() const
{
    return isintact;
}
void limb::setintact()
{
    isintact= false;
}
[[nodiscard]] float limb::gethp() const
{
    return hp;
}
void limb::sethp(float new_hp)
{
    hp=new_hp;
}
[[nodiscard]] float limb::getdmg() const
{
    return dmg;
}