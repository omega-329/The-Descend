
#include "../Header/Enemy.h"

[[nodiscard]] bool Enemies::isUnlocked() const
{
    return unlocked;
}
void Enemies::Unlock()
{
    unlocked=true;
}
void Enemies::setTexture(const sf::Texture &texture)
{
    sprite.setTexture(texture);
    // Center origin so coordinates are accurate
    sf::FloatRect bounds = sprite.getLocalBounds();
    sprite.setOrigin({bounds.size.x / 2.f, bounds.size.y / 2.f});
}
void Enemies::hitIndicator()
{
    sprite.setColor(sf::Color::Red);
}
void Enemies::resetIndicator()
{
    sprite.setColor(sf::Color::White);
}
void Enemies::setPosition(float x, float y)
{
    sprite.setPosition({x, y});
}
void Enemies::draw(sf::RenderWindow& window) const
{
    if (isAlive())
    {
        window.draw(sprite);
    }
}
Enemies::Enemies(std::string name, std::string description, std::vector<Limb> limbs)
    : Entity(name, description, limbs)
    , sprite(sprite)
{}