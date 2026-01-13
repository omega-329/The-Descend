//
// Created by omega on 04.01.2026.
//

#ifndef OOP_GAME_H
#define OOP_GAME_H
#pragma once
#include <memory>
#include "GameState.h"
#include "Weapon.h"
#include "PlayerInventory.h"

class Game
{
public:
    Game();
    void run();
    void changeState(std::unique_ptr<GameState> newState);
    sf::Font& getFont();
    sf::Texture& getPlayerTexture();
    void pushState(std::unique_ptr<GameState> newState);
    void popState();
    sf::Texture& getVesselTexture();
    sf::Texture& getSoldierTexture();
    sf::Texture& getBloatedTexture();
    sf::Texture& getSpaghettiTexture();
    sf::Texture& getShadowTexture();
    sf::Texture& getContraptionTexture();
private:
    sf::RenderWindow window;
    sf::Clock clock;
    std::vector<std::unique_ptr<GameState>> state;
    sf::Texture playerTexture;
    sf::Font font;
    sf::Texture vesselTex, soldierTex, bloatedTex, spaghettiTex, shadowTex, contraptionTex;
};
#endif //OOP_GAME_H