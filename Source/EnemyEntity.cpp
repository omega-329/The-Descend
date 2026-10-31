#include "../Header/EnemyEntity.h"

EnemyEntity::EnemyEntity(Enemies enemy,
                         const sf::Texture& texture,
                         sf::Vector2f position)
    : enemy(std::move(enemy)), sprite(texture)
{
    auto bounds = sprite.getLocalBounds();
    sprite.setOrigin({
        bounds.size.x * 0.5f,
        bounds.size.y * 0.5f
    });

    sprite.setPosition(position);
}

void EnemyEntity::update(float)
{
    if (!enemy.isAlive())
    {
    }
}

void EnemyEntity::draw(sf::RenderWindow& window)
{
    if (enemy.isAlive())
        window.draw(sprite);
}

Enemies& EnemyEntity::getEnemy()
{
    return enemy;
}
sf::FloatRect EnemyEntity::getBounds() const
{
    return sprite.getGlobalBounds();
}