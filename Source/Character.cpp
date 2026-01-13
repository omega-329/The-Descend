#include "../Header/Character.h"
#include "../Header/Limb.h"
#include <vector>
#include <iostream>

void Character::equipWeapon(const weapons& noww)
{
        currentWeapon = noww;
}

void Character::equipArmor(const armor& nowa)
{
        currentArmor = nowa;
}
bool Character::getGuarding() const
{
        return guard;
}
void Character::setGuarding(bool val)
{
        guard=val;
}
weapons& Character::getWeapon() { return currentWeapon; }
const armor& Character::getArmor() const {return currentArmor; }
