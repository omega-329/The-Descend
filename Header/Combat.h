
#ifndef OOP_COMBAT_H
#define OOP_COMBAT_H
#include <vector>
#include <string>
#include <random>
#include "Character.h"
#include "Enemy.h"
#include "Item.h"

class Combat
{
public:

    Combat(std::vector<Character>& party, Enemies enemy);

    bool isPlayerTurn() const;
    int getCurrentCharacterIndex() const;
    std::string getLastMessage() const;
    void playerPass();
    void playerGuard();
    void playerAttack(int limbIndex);
    void playerUseItem(Item& item);
    void processEnemyTurn();

    bool isVictory();
    bool isDefeat() const;

    Enemies& getEnemy() { return enemy; }

private:
    std::vector<Character>& party;
    Enemies enemy;

    int currentTurnIndex = 0;
    bool playerTurn = true;
    std::string combatLog;
    std::mt19937 gen;

    int getRandomLivingLimb(Entity& e);

    template<typename T>
    int getRandomLivingEntity(std::vector<T>& list);

    void nextTurn();
};
#endif //OOP_COMBAT_H