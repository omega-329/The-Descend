
#ifndef OOP_MENUSTATE_H
#define OOP_MENUSTATE_H
#pragma once
#include "GameState.h"
#include "Player.h"

class Game;

class PauseMenuState : public GameState
{
public:
    PauseMenuState(Game& game, sf::Font& font);
    void handleEvent(const sf::Event& event) override;
    void update(float dt) override;
    void draw(sf::RenderWindow& window) override;

private:
    Game& game;
    sf::Text text;
};
#endif //OOP_MENUSTATE_H