//
// Created by omega on 04.01.2026.
//

#ifndef OOP_PLAYSTATE_H
#define OOP_PLAYSTATE_H
#pragma once
#include "GameState.h"
#include "Player.h"
#include "Enemyentity.h"
#include <random>
#include <algorithm>
#include <vector>
#include <iostream>
#include <map>

class Game;

class PlayingState : public GameState
{
public:
    PlayingState(Game& game, sf::Texture& texture);

    void handleEvent(const sf::Event& event) override;
    void update(float dt) override;
    void draw(sf::RenderWindow& window) override;

private:
    Player player;
    Game& game;
    std::vector<EnemyEntity> enemiess;
    sf::Texture genericEnemyTexture;
    std::map<std::string, sf::Texture> battleTextures;
};
#endif //OOP_PLAYSTATE_H