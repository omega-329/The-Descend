
#include "../Header/Entity.h"
Entity::Entity(std::string name, std::string description, std::vector<Limb> limbs)
    : name(std::move(name)), description(std::move(description)), limbs(std::move(limbs))
{
}
bool Entity::isAlive() const
{
    return alive;
}
void Entity::Kill()
{
    alive = false;
}
const Limb& Entity::getLimb(int i) const
{
    return limbs[i];
}
Limb& Entity::getLimb(int i)
{
    return limbs[i];
}
const std::string& Entity::getName() const
{
    return name;
}
int Entity::getLimbCount() const
{
    return limbs.size();
}
const std::string& Entity::getDescription() const
{
    return description;
}