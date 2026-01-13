

#include "../Header/Player.h"

Player::Player(const sf::Texture& texture, float speed)
    : sprite(texture), speed(speed), velocity(0.f, 0.f)
{
    sprite.setTextureRect({ {0, 0}, {34, 60} });
    sprite.setPosition({600.f, 400.f});
}

void Player::handleInput(float dt)
{
    velocity = {0.f, 0.f};

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
        velocity.y -= speed;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
        velocity.y += speed;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
        velocity.x -= speed;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        velocity.x += speed;

    updateTexture();
}

void Player::update(float dt)
{
    sprite.move(velocity * dt);
}

void Player::updateTexture()
{
    if (velocity.y < 0)
        sprite.setTextureRect({ {102, 0}, {34, 60} });
    else if (velocity.y > 0)
        sprite.setTextureRect({ {136, 0}, {34, 60} });
    else if (velocity.x < 0)
        sprite.setTextureRect({ {68, 0}, {34, 60} });
    else if (velocity.x > 0)
        sprite.setTextureRect({ {34, 0}, {34, 60} });
    else
        sprite.setTextureRect({ {0, 0}, {34, 60} });
}

void Player::draw(sf::RenderWindow& window) const
{
    window.draw(sprite);
}

sf::Vector2f Player::getPosition() const
{
    return sprite.getPosition();
}

sf::FloatRect Player::getBounds() const
{
    return sprite.getGlobalBounds();
}
PlayerInventory& Player::getInventory()
{
    return inventory;
}
Party& Player::getParty()
{
    return party;
}