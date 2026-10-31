//
// Created by omega on 05.01.2026.
//

#ifndef OOP_INVENTORYSTATE_H
#define OOP_INVENTORYSTATE_H
#pragma once
#include "GameState.h"
#include "PlayerInventory.h"
#include "Player.h"
#include <vector>

class Game;

enum class MenuLayer {
    LAYER_CHARACTERS,
    LAYER_ACTIONS,
    LAYER_ITEMS
};

class InventoryState : public GameState
{
public:
    InventoryState(Game& game, Player& player, sf::Font& font);

    void handleEvent(const sf::Event& event) override;
    void update(float) override {}
    void draw(sf::RenderWindow& window) override;

private:
    Game& game;
    Player& player;
    sf::Font& font;

    MenuLayer currentLayer = MenuLayer::LAYER_CHARACTERS;

    int selectedCharIndex = 0;
    int selectedActionIndex = 0;
    int selectedItemIndex = 0;

    std::vector<Item*> getFilteredItems() const;

    void equipOrUseItem(Item* item) const;
};
#endif //OOP_INVENTORYSTATE_H