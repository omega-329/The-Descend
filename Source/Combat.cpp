#include "../Header/Combat.h"
Combat::Combat(std::vector<Character>& p, Enemies e)
    : party(p), enemy(std::move(e))
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

void Combat::playerAttack(int limbIndex)
{
    Character& attacker = party[currentTurnIndex];
    Enemies& target = enemy;

    float dmg = attacker.getWeapon().interact();

    Limb& limb = target.getLimb(limbIndex);
    limb.setHP(limb.getHP() - dmg);

    combatLog = attacker.getName() + " hits " + limb.getName() + " for " + std::to_string((int)dmg);

    if (limb.getHP() <= 0) {
        limb.setSevered();
        combatLog += " (Severed!)";
    }

    int severed = 0;
    for (const auto& l : target.getLimbs())
    {
        if (!l.getIntact())
            severed++;
        if (target.getLimbCount() == severed)
            target.Kill();
    }
    nextTurn();
}

void Combat::playerUseItem(Item& item)
{
    Character& user = party[currentTurnIndex];
    user.applyLimbEffect(item.interact());
    combatLog = user.getName() + " used " + item.getName() + ".";
    nextTurn();
}

void Combat::processEnemyTurn()
{
    int targetIdx   = getRandomLivingEntity(party);

    if (targetIdx == -1) {
        return;
    }

    Enemies& attacker = enemy;
    Character& target = party[targetIdx];

    int limbIdxE = getRandomLivingLimb(attacker);
    int limbIdx  = getRandomLivingLimb(target);

    if (limbIdx == -1 || limbIdxE == -1) {
        return;
    }

    float dmg = attacker.getLimb(limbIdxE).getDMG();
    if (target.getGuarding()) dmg /= 2.0f;

    Limb& limb = target.getLimb(limbIdx);
    limb.setHP(limb.getHP() - dmg);

    if (limb.getHP() <= 0)
        limb.setSevered();

    int severed = 0;

    for (const auto& l : target.getLimbs())
    {
        if (!l.getIntact())
            severed++;
        if (target.getLimbCount() == severed)
            target.Kill();
    }
    combatLog = attacker.getName() + " attacks " + target.getName() + " for " + std::to_string((int)dmg);

    playerTurn = true;
    currentTurnIndex = 0;
    for(auto& p : party) p.setGuarding(false);
}

void Combat::nextTurn()
{
    do
    {
        currentTurnIndex++;
        if (currentTurnIndex >= party.size()) {
            playerTurn = false;
            currentTurnIndex = 0;
            return;
        }
    }while (!party[currentTurnIndex].isAlive());
    playerTurn = true;
}
void Combat::playerPass()
{
    party[currentTurnIndex].setGuarding(false);
    combatLog = party[currentTurnIndex].getName() + " didn't pay attention.";
    nextTurn();
}
bool Combat::isVictory()
{
        if (!enemy.isAlive()) return true;
    return false;
}
bool Combat::isDefeat() const
{
    for (auto& hero : party) {
        if (hero.isAlive()) return false;
    }
    return true;
}