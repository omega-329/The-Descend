#ifndef OOP_MAINMENUSTATE_H
#define OOP_MAINMENUSTATE_H

#include "GameState.h"
#include <string>
#include <vector>

class Game;

class MainMenuState : public GameState
{
public:
    explicit MainMenuState(Game& game);

    void handleEvent(const sf::Event& event) override;
    void update(float dt) override;
    void draw(sf::RenderWindow& window) override;

private:
    void confirmSelection();

    Game& game;
    std::vector<std::string> options{"Begin the Hunt", "Marionettes", "Concede"};
    int menuIndex = 0;
    sf::Text title;
};


#endif //OOP_MAINMENUSTATE_H