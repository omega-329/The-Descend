
#include "../Header/Enemy.h"

void Enemies::setTexture(const sf::Texture &texture)
{
    sprite.setTexture(texture, true);
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