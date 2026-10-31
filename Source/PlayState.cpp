
#include "../Header/PlayState.h"
#include "../Header/Game.h"
#include "../Header/Pauzestate.h"
#include "../Header/InventoryState.h"
#include "../Header/ItemLoader.h"
#include "../Header/CombatState.h"
#include "../Header/EntityLoader.h"


PlayingState::PlayingState(Game& game, sf::Texture& texture)
    :  player(texture, 200.f), game(game)
{
    rng.seed(std::random_device{}());
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
    if (!genericHunterTexture.loadFromFile("../Sprite/hunter.png"))
    {
        std::cerr << "ERROR: Could not load hunter.png!" << std::endl;
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
    std::vector<int> heroIndices;
    for (int i = 0; i <= 5; ++i) heroIndices.push_back(i);
    std::shuffle(heroIndices.begin(), heroIndices.end(), rng);
    std::vector<int> enemyIndices;
    for (int i = 6; i <= 11; ++i) enemyIndices.push_back(i);
    std::shuffle(enemyIndices.begin(), enemyIndices.end(), rng);
    for (int i = 0; i < 4; ++i)
    {
        int index = heroIndices[i];

        Character partyMember(
            entities[index].getName(),
            entities[index].getDescription(),
            entities[index].getLimbs(),
            genericHunterTexture
        );
        player.getParty().addMember(std::move(partyMember));

        // The hunter is now part of your run, so the codex knows them.
        game.getCodex().markSeen(entities[index].getName());
    }
    // Monsters must never appear on top of the player: at frame 1 that would
    // mean an instant, unavoidable fight. Re-roll any spawn closer than this.
    const sf::Vector2f playerCenter = player.getBounds().getCenter();
    constexpr float kSafeSpawnDistance = 260.f;

    for (int i = 0; i < 3; ++i)
    {
        int index = enemyIndices[i];
            Enemies monster(
                entities[index].getName(),
                entities[index].getDescription(),
                entities[index].getLimbs(),
                genericEnemyTexture
            );

        std::uniform_int_distribution xDist(500, 1099);
        std::uniform_int_distribution yDist(100, 699);

        sf::Vector2f spawnPos{1099.f, 100.f};      // far corner, used only if every roll fails

        for (int attempt = 0; attempt < 64; ++attempt)
        {
            const sf::Vector2f candidate{
                static_cast<float>(xDist(rng)),
                static_cast<float>(yDist(rng))
            };

            const float dx = candidate.x - playerCenter.x;
            const float dy = candidate.y - playerCenter.y;

            if (dx * dx + dy * dy >= kSafeSpawnDistance * kSafeSpawnDistance)
            {
                spawnPos = candidate;
                break;
            }
        }

        EnemyEntity monsterWorld(std::move(monster), genericEnemyTexture, spawnPos);

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
            Enemies encounter = it->getEnemy();
            std::string enemyName = it->getEnemy().getName();
            sf::Texture& textureToUse = (battleTextures.count(enemyName))
                              ? battleTextures[enemyName]
                              : genericEnemyTexture;
            game.getCodex().markSeen(enemyName);
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