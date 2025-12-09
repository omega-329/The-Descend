#include <iostream>
#include "../Header/Enemies.h"
#include <limits>

[[nodiscard]] bool enemies::getlock() const
{
    return unlock;
}
void enemies::setlock()
{
    unlock=true;
}
[[nodiscard]] std::string enemies::getnume() const

{
    return nume;
}
[[nodiscard]] limb enemies::getlimb(int i) const
{
    return limbs[i];
};
std::istream& operator>>(std::istream& in, enemies& e)
{
    float hp, dmg;
    std::getline(in, e.nume);
    std::getline(in, e.descriere);
    for (int i=0; i<e.nrlimb; i++)
    {
        in>>hp>>dmg;
        e.limbs.emplace_back(hp,dmg);
    }
    in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return in;
}
std::ostream& operator<<(std::ostream& out,const enemies& e)
{
    out<<"Name:"<<e.nume<<std::endl;
    out<<e.descriere<<std::endl;
    return out;
}
[[nodiscard]] bool enemies::getalive() const
{
    return isalive;
}
void enemies::setalive()
{
    isalive = false;
}
[[nodiscard]] int enemies::getlimbcount() const
{
    return nrlimb;
}
void enemies::updatelimbstatus(limb climb)
{
    climb.setintact();
}
