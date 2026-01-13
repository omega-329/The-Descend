
#include "../Header/Game.h"
#include "../Header/GameState.h"
#include "../Header/PlayState.h"
#include "../Header/ItemLoader.h"
#include <SFML/Graphics/Font.hpp>
Game::Game()
    : window(sf::VideoMode({1200, 800}), "The Descent")
{
    if (!playerTexture.loadFromFile("../Sprite/Player.png"))
        throw std::runtime_error("Failed to load texture");

    if (!font.openFromFile("../Random Assets/OldLondon.ttf"))
        throw std::runtime_error("Failed to load font");

    if (!vesselTex.loadFromFile("../Sprite/Vessel.png")) {
        throw std::runtime_error("Failed to load texture");
    }
    if (!soldierTex.loadFromFile("../Sprite/Soldier.png")) {
        throw std::runtime_error("Failed to load texture");
    }
    if (!bloatedTex.loadFromFile("../Sprite/Bloated.png")) {
        throw std::runtime_error("Failed to load texture");
    }
    if (!spaghettiTex.loadFromFile("../Sprite/Spaghetti.png")) {
        throw std::runtime_error("Failed to load texture");
    }
    if (!shadowTex.loadFromFile("../Sprite/Shadow.png")) {
        throw std::runtime_error("Failed to load texture");
    }
    if (!contraptionTex.loadFromFile("../Sprite/Contraption.png")) {
        throw std::runtime_error("Failed to load texture");
    }
    state.push_back(std::make_unique<PlayingState>(*this, playerTexture));
}

void Game::run()
{
    while (window.isOpen())
    {
        while (auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
            if (!state.empty()) {
                state.back()->handleEvent(*event);
            }
        }

        float dt = clock.restart().asSeconds();
        if (!state.empty()) {
            state.back()->update(dt);
        }
        window.clear();
        if (!state.empty()) {
            state.back()->draw(window);
        }
        window.display();
    }
}

void Game::changeState(std::unique_ptr<GameState> newState)
{
    state.clear();
    state.push_back(std::move(newState));
}

sf::Font& Game::getFont()
{
    return font;
}
sf::Texture& Game::getPlayerTexture()
{
    return playerTexture;
}
void Game::pushState(std::unique_ptr<GameState> newState) {
    state.push_back(std::move(newState));
}

void Game::popState() {
    if (!state.empty()) {
        state.pop_back();
    }
}
sf::Texture& Game::getVesselTexture() { return vesselTex; }
sf::Texture& Game::getSoldierTexture() { return soldierTex; }
sf::Texture& Game::getBloatedTexture() { return bloatedTex; }
sf::Texture& Game::getSpaghettiTexture() { return spaghettiTex; }
sf::Texture& Game::getShadowTexture() { return shadowTex; }
sf::Texture& Game::getContraptionTexture() { return contraptionTex; }
