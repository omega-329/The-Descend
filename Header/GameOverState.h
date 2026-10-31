//
// Created by omega on 12.10.2026.
//

#ifndef OOP_GAMEOVERSTATE_H
#define OOP_GAMEOVERSTATE_H
#include "GameState.h"
#include <SFML/Graphics.hpp>

class Game;

class GameOverState : public GameState
{
public:
    explicit GameOverState(Game& game);

    void handleEvent(const sf::Event& event) override;
    void update(float dt) override;
    void draw(sf::RenderWindow& window) override;

private:
    void confirmSelection();

    Game& game;
    sf::Text title;
    sf::Text retryText;
    sf::Text quitText;

    int menuIndex = 0;
    float inputDelay = 0.4f;
};
#endif //OOP_GAMEOVERSTATE_H