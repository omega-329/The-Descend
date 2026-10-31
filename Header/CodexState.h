#ifndef OOP_CODEXSTATE_H
#define OOP_CODEXSTATE_H
#pragma once

#include "GameState.h"
#include "Codex.h"
#include <string>
#include <vector>

class Game;

// Three equal columns:
//   1. the list of monsters + characters
//   2. the selected entity's portrait
//   3. top = description, bottom = limb stats, paginated like a book
//
// Monsters and hunters alike start locked: name shows as "???", no portrait,
// no description and no stats. Monsters unlock when a fight begins, hunters
// unlock when they join your party for the run.
class CodexState : public GameState
{
public:
    explicit CodexState(Game& game);

    void handleEvent(const sf::Event& event) override;
    void update(float dt) override;
    void draw(sf::RenderWindow& window) override;

private:
    struct Entry
    {
        const Entity* entity = nullptr;
    };

    void moveSelection(int delta);
    [[nodiscard]] bool isLocked(int index) const;

    // Stats are split into fixed-size pages, one page per Left/Right press.
    [[nodiscard]] int pageCount() const;
    [[nodiscard]] int lastPage() const;

    void drawList(sf::RenderWindow& window, sf::Font& font) const;
    void drawPortrait(sf::RenderWindow& window, sf::Font& font) const;
    void drawDescription(sf::RenderWindow& window, sf::Font& font) const;
    void drawStats(sf::RenderWindow& window, sf::Font& font) const;

    Game& game;
    const std::vector<Entity>& monsters;
    const std::vector<Entity>& characters;

    std::vector<Entry> entries;
    std::vector<std::string> wrappedDescriptions;

    int selected = 0;
    int statsPage = 0;

    sf::Text title;
    sf::Text hint;
};

#endif //OOP_CODEXSTATE_H
