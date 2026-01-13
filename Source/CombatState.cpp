
#include "../Header/CombatState.h"
#include "../Header/Game.h"
#include <iostream>

CombatState::CombatState(Game& game, Player& player, std::vector<Enemies> enemies, const sf::Texture& enemyTex)
    : game(game)
    , playerRef(player)
    , combatSystem(player.getParty().getMembers(), enemies)
{
    uiBox.setSize({1200.f, 200.f});
    uiBox.setPosition({0.f, 600.f});
    uiBox.setFillColor(sf::Color(30, 30, 30));

    auto& liveEnemies = combatSystem.getEnemies();

    float startX = 800.f;
    float startY = 200.f;
    float spacing = 150.f;

    for (size_t i = 0; i < liveEnemies.size(); ++i) {
        liveEnemies[i].setTexture(enemyTex);
        liveEnemies[i].setPosition(startX + i * spacing, startY);
    }
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

    if (!combatSystem.isPlayerTurn()) {
        enemyTurnTimer += dt;
        if (enemyTurnTimer > 1.0f) {
            combatSystem.processEnemyTurn();
            enemyTurnTimer = 0.f;
        }
    }
    if (combatSystem.isVictory())
    {
        battleOver = true;
    }
    if (combatSystem.isDefeat())
    {
        std::cout << "GAME OVER" << std::endl;
        game.popState();
        return;
    }
}

void CombatState::handleEvent(const sf::Event& event)
{
    if (auto* keyEvent = event.getIf<sf::Event::KeyPressed>())
    {
        sf::Keyboard::Key key = keyEvent->code;
        if (!combatSystem.isPlayerTurn()) return;
        if (subState == SubState::SelectingAction) {
            if (key == sf::Keyboard::Key::Up)   menuIndex = 0;
            if (key == sf::Keyboard::Key::Down) menuIndex = 1;

            if (key == sf::Keyboard::Key::Enter || key == sf::Keyboard::Key::Space) {
                if (menuIndex == 0) {
                    subState = SubState::SelectingLimb;
                    limbIndex = 0;
                } else {
                    combatSystem.playerGuard();
                }
            }
        }
        else if (subState == SubState::SelectingLimb) {
            auto& targets = combatSystem.getEnemies();
            if (targets.empty()) return;

            int maxLimbs = targets[0].getLimbCount();
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
                combatSystem.playerAttack(0, limbIndex);
                subState = SubState::SelectingAction;
            }
        }
    }
}

void CombatState::draw(sf::RenderWindow& window)
{
    window.clear(sf::Color::Black);

    auto& enemies = combatSystem.getEnemies();
    for (auto& e : enemies)
    {
        bool alive = false;
        for(int i=0; i<e.getLimbCount(); ++i) {
            if(e.getLimb(i).getHP() > 0) { alive = true; break; }
        }

        if (alive) {
            e.draw(window);
        }
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
            sf::Text atk(font, "Attack", 30);
            atk.setPosition({400, 620});
            atk.setFillColor(menuIndex == 0 ? sf::Color::Yellow : sf::Color::White);

            sf::Text grd(font, "Guard", 30);
            grd.setPosition({400, 660});
            grd.setFillColor(menuIndex == 1 ? sf::Color::Yellow : sf::Color::White);

            window.draw(atk);
            window.draw(grd);
        }
        else if (subState == SubState::SelectingLimb) {
            if (!enemies.empty()) {
                Enemies& target = enemies[0];

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
        }
    }
    if (battleOver)
    {
        sf::Text winText(game.getFont(), "VICTORY!", 60);
        winText.setPosition({500, 300});
        winText.setFillColor(sf::Color::Green);
        window.draw(winText);

    }

    sf::Text log(font, combatSystem.getLastMessage(), 20);
    log.setPosition({10, 10});
    window.draw(log);
}