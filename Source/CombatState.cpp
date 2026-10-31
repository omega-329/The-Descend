

#include "../Header/CombatState.h"
#include "../Header/Game.h"
#include "../Header/GameOverState.h"
#include <iostream>

CombatState::CombatState(Game& game, Player& player, Enemies enemy, const sf::Texture& enemyTex)
    : game(game)
    , playerRef(player)
    , combatSystem(player.getParty().getMembers(), enemy)
{
    uiBox.setSize({1200.f, 200.f});
    uiBox.setPosition({0.f, 600.f});
    uiBox.setFillColor(sf::Color(30, 30, 30));

    auto& liveEnemies = combatSystem.getEnemy();

    liveEnemies.setTexture(enemyTex);
    liveEnemies.setPosition(600.f, 400.f);
}

void CombatState::update(float dt)
{
    if (battleOver)
    {
        endBattleTimer += dt;
        if (endBattleTimer > 2.0f)
        {
            game.popState();
        }
        return;
    }
    if (combatSystem.isVictory())
    {
        battleOver = true;
    }
    if (combatSystem.isDefeat())
    {
        game.changeState(std::make_unique<GameOverState>(game));
        return;
    }
    if (!combatSystem.isDefeat() && !combatSystem.isVictory())
    {
        if (!combatSystem.isPlayerTurn()) {
            enemyTurnTimer += dt;
            if (enemyTurnTimer > 1.0f) {
                combatSystem.processEnemyTurn();
                enemyTurnTimer = 0.f;
            }
    }
        }
    }
void CombatState::handleEvent(const sf::Event& event)
{
    if (battleOver) return;
    if (auto* keyEvent = event.getIf<sf::Event::KeyPressed>())
    {
        sf::Keyboard::Key key = keyEvent->code;
        if (!combatSystem.isPlayerTurn()) return;
        if (subState == SubState::SelectingAction) {
            const int count = static_cast<int>(actionOptions.size());
            if (key == sf::Keyboard::Key::Up)   menuIndex = (menuIndex - 1 + count) % count;
            if (key == sf::Keyboard::Key::Down) menuIndex = (menuIndex + 1) % count;

            if (key == sf::Keyboard::Key::Enter || key == sf::Keyboard::Key::Space) {
                switch (menuIndex) {
                    case 0:  // Attack
                        subState = SubState::SelectingLimb;
                        limbIndex = 0;
                        break;
                    case 1:  // Guard
                        combatSystem.playerGuard();
                        break;
                    case 2:  // Item
                        subState = SubState::SelectingItem;
                        itemIndex = 0;
                        break;
                    default:
                        combatSystem.playerPass();
                        break;
                }
            }
        }
        else if (subState == SubState::SelectingLimb) {
            auto& target = combatSystem.getEnemy();
            if (!target.isAlive()) return;
            int maxLimbs = target.getLimbCount();
            if (key == sf::Keyboard::Key::Up)
            {
                limbIndex--;
                if (limbIndex < 0) {
                    limbIndex = maxLimbs - 1;
                    scrollOffset = std::max(0, maxLimbs - VISIBLE_ITEMS);
                }
                if (limbIndex < scrollOffset) {
                    scrollOffset = limbIndex;
                }
            }
            if (key == sf::Keyboard::Key::Down)
            {
                limbIndex++;
                if (limbIndex >= maxLimbs) {
                    limbIndex = 0;
                    scrollOffset = 0;
                }
                if (limbIndex >= scrollOffset + VISIBLE_ITEMS) {
                    scrollOffset = limbIndex - VISIBLE_ITEMS + 1;
                }
            }
            if (key == sf::Keyboard::Key::Escape) subState = SubState::SelectingAction;

            if (key == sf::Keyboard::Key::Enter || key == sf::Keyboard::Key::Space) {
                combatSystem.playerAttack(limbIndex);
                subState = SubState::SelectingAction;
            }
        } else if (subState == SubState::SelectingItem) {
            auto consumables = playerRef.getInventory().getConsumables();
            if (consumables.empty()) {
                subState = SubState::SelectingAction;
                return;
            }
            const int count = static_cast<int>(consumables.size());
            if (key == sf::Keyboard::Key::Up) {
                itemIndex = (itemIndex - 1 + count) % count;
            } else if (key == sf::Keyboard::Key::Down) {
                itemIndex = (itemIndex + 1) % count;
            } else if (key == sf::Keyboard::Key::Escape) {
                subState = SubState::SelectingAction;
            } else if (key == sf::Keyboard::Key::Enter || key == sf::Keyboard::Key::Space) {
                Item* item = consumables[itemIndex];
                combatSystem.playerUseItem(*item);
                playerRef.getInventory().consume(item);
                subState = SubState::SelectingAction;
                itemIndex = 0;
            }
        }
    }
}

void CombatState::draw(sf::RenderWindow& window)
{
    window.clear(sf::Color::Black);

    auto& enemies = combatSystem.getEnemy();
        bool alive = false;
        for(int i=0; i<enemies.getLimbCount(); ++i) {
            if(enemies.getLimb(i).getHP() > 0) { alive = true; break; }
        }

        if (alive) {
            enemies.draw(window);
        }

    window.draw(uiBox);
    sf::Font& font = game.getFont();

    auto& party = playerRef.getParty().getMembers();
    int activeIdx = combatSystem.getCurrentCharacterIndex();

    for (int i = 0; i < party.size(); ++i) {
        sf::Text nameText(font, party[i].getName(), 24);
        nameText.setPosition({50, 620.f + i * 30.f});

        if (combatSystem.isPlayerTurn() && i == activeIdx)
            nameText.setFillColor(sf::Color(255, 165, 0));
        else
            nameText.setFillColor(sf::Color::White);

        window.draw(nameText);
    }

    if (combatSystem.isPlayerTurn()) {
        if (subState == SubState::SelectingAction) {
            for (int i = 0; i < static_cast<int>(actionOptions.size()); ++i) {
                sf::Text optionText(font, actionOptions[i], 30);
                optionText.setPosition({400.f, 620.f + i * 40.f});   // 620, 660 -> same as before
                optionText.setFillColor(i == menuIndex ? sf::Color::Yellow : sf::Color::White);
                window.draw(optionText);
            }
        }
        else if (subState == SubState::SelectingLimb) {
            if (enemies.isAlive()) {
                Enemies& target = enemies;

                int start = scrollOffset;
                int end = std::min(target.getLimbCount(), scrollOffset + VISIBLE_ITEMS);

                int displayIndex = 0;

                for(int i = start; i < end; ++i)
                {
                    Limb& l = target.getLimb(i);
                    std::string str = l.getName() + " (" + std::to_string((int)l.getHP()) + ")";
                    sf::Text limbTxt(font, str, 24);
                    if (i == limbIndex) {
                        limbTxt.setFillColor(sf::Color::Red);
                        str += " <";
                        limbTxt.setString(str);
                    } else {
                        limbTxt.setFillColor(sf::Color::White);
                    }
                    limbTxt.setPosition({400.f, 620.f + displayIndex * 30.f});

                    window.draw(limbTxt);

                    displayIndex++;
                }
                if (scrollOffset > 0) {
                    sf::Text upArrow(font, "^ MORE ^", 20);
                    upArrow.setPosition({400, 595});
                    upArrow.setFillColor(sf::Color::Yellow);
                    window.draw(upArrow);
                }
                if (scrollOffset + VISIBLE_ITEMS < target.getLimbCount()) {
                    sf::Text downArrow(font, "v MORE v", 20);
                    downArrow.setPosition({400.f, 620.f + VISIBLE_ITEMS * 30.f});
                    downArrow.setFillColor(sf::Color::Yellow);
                    window.draw(downArrow);
                }
             }
        } else if (subState == SubState::SelectingItem) {
            auto consumables = playerRef.getInventory().getConsumables();
            if (consumables.empty()) {
                sf::Text emptyText(font, "No items.", 24);
                emptyText.setPosition({400.f, 620.f});
                emptyText.setFillColor(sf::Color::White);
                window.draw(emptyText);
            } else {
                for (int i = 0; i < (int)consumables.size(); ++i) {
                    std::string label = consumables[i]->getName();
                    if (consumables[i]->getQuantity() > 1)
                        label += " x" + std::to_string(consumables[i]->getQuantity());
                    sf::Text t(font, label, 24);
                    t.setPosition({400.f, 620.f + i * 30.f});
                    if (i == itemIndex)
                        t.setFillColor(sf::Color::Yellow);
                    else
                        t.setFillColor(sf::Color::White);
                    window.draw(t);
                }
            }
        }
    }
    sf::Text log(font, combatSystem.getLastMessage(), 20);
    log.setPosition({10, 10});
    window.draw(log);
}
