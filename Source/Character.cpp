#include "../Header/Character.h"
#include "../Header/Limb.h"
#include <vector>
#include <iostream>
#include <limits>

bool character::getlock() const
{
    return unlock;
}
[[nodiscard]] limb character::getlimb(int i) const
{
    return limbs[i];
}
void character::setlock()
{
    unlock = true;
}
[[nodiscard]] std::string& character::getnume()
{
    return nume;
}
std::istream& operator>>(std::istream& in, character& p)
{
    float hp, dmg;
    std::getline(in ,p.nume);
    std::getline(in,p.descriere);
    p.limbs.reserve(p.nrlimb);
    for (int i=0; i<p.nrlimb; i++)
    {
        in>>hp>>dmg;
        p.limbs.emplace_back(hp,dmg);
    }
    in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return in;
}
std::ostream& operator<<(std::ostream& out,const character& p)
{
    out<<"Name:"<<p.nume<<std::endl;
    out<<p.descriere<<std::endl<<std::endl;
    return out;
}
weapons character::equipweapon(const weapons& noww)
{
    if (noww.getweapon() && !noww.getequip())
        currentweapon =noww;
}
armor character::equiparmor(const armor& nowa)
{
    if (nowa.getarmor() && !nowa.getequiped())
        currentarmor = nowa;
}
[[nodiscard]] bool character::getalive() const
{
    return isalive;
}
void character::setalive()
{
    isalive = false;
}
[[nodiscard]] int character::getlimbcount() const
{
    return nrlimb;
}
void character::updatelimbstatus(limb climb)
{
    climb.setintact();
}
weapons& character::getcurrentweapon() { return currentweapon; }
