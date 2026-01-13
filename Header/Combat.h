
#ifndef OOP_COMBAT_H
#define OOP_COMBAT_H
#include <vector>
#include <string>
#include <random>
#include "Character.h"
#include "Enemy.h"

class Combat
{
public:

    Combat(std::vector<Character>& party, std::vector<Enemies> enemies);

    bool isPlayerTurn() const;
    int getCurrentCharacterIndex() const;
    std::string getLastMessage() const;

    void playerGuard();
    void playerAttack(int enemyIndex, int limbIndex);
    void processEnemyTurn();

    bool isVictory();
    bool isDefeat() const;

    std::vector<Enemies>& getEnemies() { return enemies; }

private:
    std::vector<Character>& party;
    std::vector<Enemies> enemies;

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