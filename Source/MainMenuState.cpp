#include "../Header/MainMenuState.h"
#include "../Header/Game.h"
#include "../Header/PlayState.h"
#include "../Header/CodexState.h"
#include <memory>

MainMenuState::MainMenuState(Game& game)
    : game(game)
    , title(game.getFont(), "THE DESCENT", 72)
{
    title.setOrigin(title.getLocalBounds().getCenter());
    title.setPosition({600.f, 160.f});
}

void MainMenuState::handleEvent(const sf::Event& event)
{
    auto* key = event.getIf<sf::Event::KeyPressed>();
    if (!key) return;

    const int count = static_cast<int>(options.size());

    if (key->code == sf::Keyboard::Key::Down)
        menuIndex = (menuIndex + 1) % count;
    else if (key->code == sf::Keyboard::Key::Up)
        menuIndex = (menuIndex - 1 + count) % count;
    else if (key->code == sf::Keyboard::Key::Enter || key->code == sf::Keyboard::Key::Space)
        confirmSelection();
}

void MainMenuState::confirmSelection()
{
    if (menuIndex == 0) {
        game.changeState(std::make_unique<PlayingState>(game, game.getPlayerTexture()));
        return;                       // 'this' is destroyed after changeState
    }
    if (menuIndex == 1) {
        game.pushState(std::make_unique<CodexState>(game));  // later
        return;
    }
    game.quit();
}

void MainMenuState::update(float) {}

void MainMenuState::draw(sf::RenderWindow& window)
{
    window.clear(sf::Color(10, 10, 10));
    window.draw(title);

    sf::Font& font = game.getFont();
    for (int i = 0; i < static_cast<int>(options.size()); ++i) {
        sf::Text label(font, options[i], 36);
        label.setOrigin(label.getLocalBounds().getCenter());
        label.setPosition({600.f, 380.f + i * 60.f});

        if (i == menuIndex) {
            label.setFillColor(sf::Color::Red);
            label.setStyle(sf::Text::Bold);
        } else {
            label.setFillColor(sf::Color(150, 150, 150));
        }
        window.draw(label);
    }
}