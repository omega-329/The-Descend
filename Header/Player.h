

#ifndef OOP_PLAYER_H
#define OOP_PLAYER_H

#include <SFML/Graphics.hpp>
#include "PlayerInventory.h"
#include "Character.h"
#include "Party.h"

class Player
{
public:
    Player(const sf::Texture& texture, float speed);

    void handleInput(float dt);
    void update(float dt);
    void draw(sf::RenderWindow& window) const;

    sf::Vector2f getPosition() const;
    sf::FloatRect getBounds() const;
    PlayerInventory& getInventory();
    Party& getParty();

private:
    sf::Sprite sprite;
    float speed;
    sf::Vector2f velocity;
    PlayerInventory inventory;
    Party party;

    void updateTexture();
};

#endif // OOP_PLAYER_H