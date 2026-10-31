
#include "../Header/Entity.h"

namespace
{
    // Lives as long as the program, so a sprite pointing at it can never dangle.
    // Data-only entities (the ones from EntityLoader) never draw their sprite,
    // but sf::Sprite has no default constructor, so it still needs a texture.
    const sf::Texture& blankTexture()
    {
        static const sf::Texture blank;
        return blank;
    }
}

Entity::Entity(std::string name, std::string description, std::vector<Limb> limbs, const sf::Texture& texture)
    : name(std::move(name)), description(std::move(description)), limbs(std::move(limbs)), sprite(texture)
{}
Entity::Entity(std::string name, std::string description, std::vector<Limb> limbs)
    : name(std::move(name)), description(std::move(description)), limbs(std::move(limbs)), sprite(blankTexture())
{}
bool Entity::isAlive() const
{
    return alive;
}
void Entity::Kill()
{
    alive = false;
}
bool Entity::isUnlocked() const
{
    return unlocked;
}
void Entity::Unlock()
{
    unlocked = true;
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