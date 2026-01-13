
#include "../Header/MenuState.h"
#include "../Header/Game.h"
#include "../Header/PlayState.h"

PauseMenuState::PauseMenuState(Game& game, sf::Font& font)
    : game(game), text(font, "PAUSED\nPress Esc to resume", 36)
{
    text.setPosition({300.f, 300.f});
}

void PauseMenuState::handleEvent(const sf::Event& event)
{
    if (event.is<sf::Event::KeyPressed>() &&
        event.getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Escape)
    {
        game.popState();
    }
}

void PauseMenuState::draw(sf::RenderWindow& window)
{
    window.draw(text);
}
void PauseMenuState::update(float)
{

}