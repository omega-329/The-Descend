#include "../Header/GameOverState.h"
#include "../Header/Game.h"
#include "../Header/PlayState.h"

GameOverState::GameOverState(Game& game)
    : game(game)
    , title(game.getFont(), "GAME OVER", 80)
    , retryText(game.getFont(), "Retry", 40)
    , quitText(game.getFont(), "Quit", 40)
{
    title.setFillColor(sf::Color::Red);
    title.setStyle(sf::Text::Bold);
    title.setOrigin(title.getLocalBounds().getCenter());
    title.setPosition({600.f, 300.f});          // window is 1200x800

    retryText.setOrigin(retryText.getLocalBounds().getCenter());
    retryText.setPosition({600.f, 480.f});

    quitText.setOrigin(quitText.getLocalBounds().getCenter());
    quitText.setPosition({600.f, 540.f});
}

void GameOverState::update(float dt)
{
    if (inputDelay > 0.f)
        inputDelay -= dt;
}

void GameOverState::handleEvent(const sf::Event& event)
{
    if (inputDelay > 0.f) return;

    auto* key = event.getIf<sf::Event::KeyPressed>();
    if (!key) return;

    if (key->code == sf::Keyboard::Key::Up || key->code == sf::Keyboard::Key::Down)
        menuIndex = 1 - menuIndex;
    else if (key->code == sf::Keyboard::Key::Escape)
        game.quit();
    else if (key->code == sf::Keyboard::Key::Enter || key->code == sf::Keyboard::Key::Space)
        confirmSelection();
}

void GameOverState::confirmSelection()
{
    if (menuIndex == 0)
    {
        game.changeState(std::make_unique<PlayingState>(game, game.getPlayerTexture()));
        return;
    }
    game.quit();
}

void GameOverState::draw(sf::RenderWindow& window)
{
    window.clear(sf::Color(25, 0, 0));          // near-black red backdrop

    window.draw(title);

    retryText.setFillColor(menuIndex == 0 ? sf::Color::Red : sf::Color(140, 140, 140));
    retryText.setStyle(menuIndex == 0 ? sf::Text::Bold : sf::Text::Regular);
    quitText .setFillColor(menuIndex == 1 ? sf::Color::Red : sf::Color(140, 140, 140));
    quitText .setStyle(menuIndex == 1 ? sf::Text::Bold : sf::Text::Regular);
    window.draw(retryText);
    window.draw(quitText);
}