
#include "../Header/PlayState.h"
#include "../Header/Game.h"
#include "../Header/MenuState.h"
#include "../Header/InventoryState.h"
#include "../Header/ItemLoader.h"
#include "../Header/CombatState.h"
#include "../Header/EntityLoader.h"

PlayingState::PlayingState(Game& game, sf::Texture& texture)
    :  player(texture, 200.f), game(game)
{
    auto items = loadItemsFromFile("../Data_folder/thebusiness.txt");
    for (auto& item : items)
        player.getInventory().addItem(std::move(item));

    auto entities = loadEntities("../Data_folder/entities.txt");

    if (entities.size() != 12) {
        throw std::runtime_error(
            "entities.txt must contain exactly 12 entities, found " +
            std::to_string(entities.size())
        );
    }

    if (!genericEnemyTexture.loadFromFile("../Sprite/enemy.png"))
    {
        std::cerr << "ERROR: Could not load enemy.png!" << std::endl;
    }
    std::vector<std::string> textureNames = {"Vessel","Soldier","Bloated", "Spaghetti", "Shadow",  "Contraption"};
    for (const auto& name : textureNames) {
        sf::Texture tex;
        if (tex.loadFromFile("../Sprite/" + name + ".png")) {
            battleTextures[name] = std::move(tex);
        } else {
            std::cerr << "Warning: Missing battle texture for " << name << std::endl;
            battleTextures[name] = genericEnemyTexture;
        }
    }
    std::random_device rd;
    std::mt19937 g(rd());
    std::vector<int> heroIndices;
    for (int i = 0; i <= 5; ++i) heroIndices.push_back(i);
    std::shuffle(heroIndices.begin(), heroIndices.end(), g);
    std::vector<int> enemyIndices;
    for (int i = 6; i <= 11; ++i) enemyIndices.push_back(i);
    std::shuffle(enemyIndices.begin(), enemyIndices.end(), g);
    for (int i = 0; i < 4; ++i)
    {
        int index = heroIndices[i];

        Character partyMember(
            entities[index].getName(),
            entities[index].getDescription(),
            entities[index].getLimbs()
        );
        player.getParty().addMember(std::move(partyMember));
    }
    for (int i = 0; i < 3; ++i)
    {
        int index = enemyIndices[i];
            Enemies monster(
                entities[index].getName(),
                entities[index].getDescription(),
                entities[index].getLimbs()
            );

            float randX = 500.f + static_cast<float>(rand() % 600);
            float randY = 100.f + static_cast<float>(rand() % 600);

        EnemyEntity monsterWorld(std::move(monster), genericEnemyTexture, {randX, randY});

            enemiess.push_back(std::move(monsterWorld));
    }
}

void PlayingState::handleEvent(const sf::Event& event)
{
    if (event.is<sf::Event::KeyPressed>() &&
        event.getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Escape)
    {
        game.pushState(std::make_unique<PauseMenuState>(game, game.getFont()));
    }
    if (event.is<sf::Event::KeyPressed>() &&
        event.getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::I)
    {
        game.pushState(std::make_unique<InventoryState>(game, player, game.getFont()));

    }
}

void PlayingState::update(float dt)
{
    player.handleInput(dt);
    player.update(dt);

    for (auto& e : enemiess) {
        e.update(dt);
    }
    for (auto it = enemiess.begin(); it != enemiess.end();)
    {
        if (player.getBounds().findIntersection(it->getBounds()))
        {
            std::vector<Enemies> encounter;
            encounter.push_back(it->getEnemy());
            std::string enemyName = it->getEnemy().getName();
            sf::Texture& textureToUse = (battleTextures.count(enemyName))
                              ? battleTextures[enemyName]
                              : genericEnemyTexture;
            game.pushState(std::make_unique<CombatState>(game, player, encounter, textureToUse));

            it = enemiess.erase(it);
            return;
        }
        else {
            ++it;
        }
    }
}

void PlayingState::draw(sf::RenderWindow& window)
{
    player.draw(window);
    for (auto& e : enemiess)
        e.draw(window);
}