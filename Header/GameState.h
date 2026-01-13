
#ifndef OOP_GAMESTATE_H
#define OOP_GAMESTATE_H
#pragma once
#include <SFML/Graphics.hpp>

class GameState
{
public:
    virtual ~GameState() = default;

    virtual void handleEvent(const sf::Event& event) = 0;
    virtual void update(float dt) = 0;
    virtual void draw(sf::RenderWindow& window) = 0;
};
#endif //OOP_GAMESTATE_H