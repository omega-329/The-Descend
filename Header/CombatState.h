

#ifndef OOP_COMBATSTATE_H
#define OOP_COMBATSTATE_H
#include "GameState.h"
#include "Combat.h"
#include "Player.h"
// REMOVE: #include "CombatEnemy.h" <-- Delete this file from your project too if you can

class Game;

enum class SubState {
    SelectingAction,
    SelectingLimb,
    ProcessingTurn
};

class CombatState : public GameState
{
public:
    CombatState(Game& game, Player& player, std::vector<Enemies> enemies, const sf::Texture& enemyTex);

    void handleEvent(const sf::Event& event) override;
    void update(float dt) override;
    void draw(sf::RenderWindow& window) override;

private:
    Game& game;
    Player& playerRef;

    Combat combatSystem;

    SubState subState = SubState::SelectingAction;
    int menuIndex = 0;
    int limbIndex = 0;

    sf::RectangleShape uiBox;
    float enemyTurnTimer = 0.0f;

    float endBattleTimer = 0.0f;
    bool battleOver = false;
    int scrollOffset = 0;
    const int VISIBLE_ITEMS = 5;
};
#endif //OOP_COMBATSTATE_H