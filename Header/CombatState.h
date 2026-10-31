

#ifndef OOP_COMBATSTATE_H
#define OOP_COMBATSTATE_H
#include "GameState.h"
#include "Combat.h"
#include "Player.h"
#include <vector>
#include <string>

class Game;

enum class SubState {
    SelectingAction,
    SelectingLimb,
    SelectingItem
};

class CombatState : public GameState
{
public:
    CombatState(Game& game, Player& player, Enemies enemy, const sf::Texture& enemyTex);

    void handleEvent(const sf::Event& event) override;
    void update(float dt) override;
    void draw(sf::RenderWindow& window) override;

private:
    Game& game;
    Player& playerRef;

    Combat combatSystem;

    SubState subState = SubState::SelectingAction;
    const std::vector<std::string> actionOptions{"Attack", "Guard", "Item"};
    int menuIndex = 0;
    int limbIndex = 0;
    int itemIndex = 0;

    sf::RectangleShape uiBox;
    float enemyTurnTimer = 0.0f;

    float endBattleTimer = 0.0f;
    bool battleOver = false;
    int scrollOffset = 0;
    const int VISIBLE_ITEMS = 5;
};
#endif //OOP_COMBATSTATE_H