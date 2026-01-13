#include "../Header/Combat.h"
Combat::Combat(std::vector<Character>& p, std::vector<Enemies> e)
    : party(p), enemies(std::move(e))
{
    std::random_device rd;
    gen.seed(rd());
}


int Combat::getRandomLivingLimb(Entity& e)
{
    std::vector<int> valid;
    for (int i = 0; i < e.getLimbCount(); ++i)
        if (e.getLimb(i).getHP() > 0) valid.push_back(i);

    if (valid.empty()) return -1;
    std::uniform_int_distribution<> dist(0, valid.size() - 1);
    return valid[dist(gen)];
}

template<typename T>
int Combat::getRandomLivingEntity(std::vector<T>& list)
{
    std::vector<int> alive;
    for (int i = 0; i < list.size(); ++i) {
        if (list[i].isAlive()) alive.push_back(i);
    }
    if (alive.empty()) return -1;

    std::uniform_int_distribution<> dist(0, alive.size() - 1);
    return alive[dist(gen)];
}

template int Combat::getRandomLivingEntity<Character>(std::vector<Character>&);
template int Combat::getRandomLivingEntity<Enemies>(std::vector<Enemies>&);


bool Combat::isPlayerTurn() const { return playerTurn; }
int Combat::getCurrentCharacterIndex() const { return currentTurnIndex; }
std::string Combat::getLastMessage() const { return combatLog; }

void Combat::playerGuard()
{
    party[currentTurnIndex].setGuarding(true);
    combatLog = party[currentTurnIndex].getName() + " guards.";
    nextTurn();
}

void Combat::playerAttack(int enemyIndex, int limbIndex)
{
    Character& attacker = party[currentTurnIndex];
    Enemies& target = enemies[enemyIndex];

    float dmg = attacker.getWeapon().interact();

    Limb& limb = target.getLimb(limbIndex);
    limb.setHP(limb.getHP() - dmg);

    combatLog = attacker.getName() + " hits " + limb.getName() + " for " + std::to_string((int)dmg);

    if (limb.getHP() <= 0) {
        limb.setIntact();
        combatLog += " (Severed!)";
    }

    // Check if enemy died (simple check: if Head/Torso is gone, or all limbs gone)
    // For now, let's just leave them 'alive' but broken

    nextTurn();
}

void Combat::processEnemyTurn()
{
    int attackerIdx = getRandomLivingEntity(enemies);
    int targetIdx   = getRandomLivingEntity(party);

    if (attackerIdx == -1 || targetIdx == -1) {
        nextTurn(); return;
    }

    Enemies& attacker = enemies[attackerIdx];
    Character& target = party[targetIdx];

    int limbIdxE = getRandomLivingLimb(attacker);
    int limbIdx  = getRandomLivingLimb(target);

    if (limbIdx == -1 || limbIdxE == -1) {
        nextTurn(); return;
    }

    float dmg = attacker.getLimb(limbIdxE).getDMG();
    if (target.getGuarding()) dmg /= 2.0f;

    Limb& limb = target.getLimb(limbIdx);
    limb.setHP(limb.getHP() - dmg);

    combatLog = attacker.getName() + " attacks " + target.getName() + " for " + std::to_string((int)dmg);

    playerTurn = true;
    currentTurnIndex = 0;
    for(auto& p : party) p.setGuarding(false);
}

void Combat::nextTurn()
{
    currentTurnIndex++;
    if (currentTurnIndex >= party.size()) {
        playerTurn = false;
        currentTurnIndex = 0;
        return;
    } while (!party[currentTurnIndex].isAlive());
    playerTurn = true;
}
bool Combat::isVictory()
{
    for (auto& enemy : enemies)
    {
        bool isAlive = false;
        for (int i = 0; i < enemy.getLimbCount(); ++i)
        {
            if (enemy.getLimb(i).getHP() > 0)
            {
                isAlive = true;
                break;
            }
        }
        if (isAlive) return false;
    }
    return true;
}
bool Combat::isDefeat() const
{
    for (auto& hero : party) {
        if (hero.isAlive()) return false;
    }
    return true;
}