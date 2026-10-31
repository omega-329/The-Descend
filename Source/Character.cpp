#include "../Header/Character.h"

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
void Character::applyLimbEffect(float amount)
{
    for (int i = 0; i < getLimbCount(); ++i) {
        getLimb(i).setHP(getLimb(i).getHP() + amount);
    }
}
