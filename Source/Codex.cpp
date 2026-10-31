#include "../Header/Codex.h"
#include "../Header/EntityLoader.h"

#include <fstream>
#include <iostream>
#include <utility>

void Codex::load(const std::string& entitiesFile,
                 const std::string& spriteDir,
                 const std::string& unlockFile)
{
    auto all = loadEntities(entitiesFile);

    // entities.txt layout: first half = playable characters, second half = monsters.
    // This is the same split PlayingState uses (indices 0..5 and 6..11).
    const std::size_t half = all.size() / 2;

    m_characters.assign(all.begin(), all.begin() + half);
    m_monsters.assign(all.begin() + half, all.end());

    m_unlockFile = unlockFile;

    if (!m_fallback.loadFromFile(spriteDir + "enemy.png"))
        std::cerr << "Codex: missing fallback texture enemy.png" << std::endl;

    auto loadTexture = [&](const std::string& name, const std::string& fallback)
    {
        sf::Texture tex;
        if (!tex.loadFromFile(spriteDir + name + ".png"))
        {
            // Character portraits mostly don't exist yet, so everyone gets
            // hunter.png until a "<Name>.png" is dropped into Sprite/.
            if (!tex.loadFromFile(spriteDir + fallback))
                std::cerr << "Codex: no texture for " << name << std::endl;
        }
        m_textures[name] = std::move(tex);
    };

    for (const auto& character : m_characters)
        loadTexture(character.getName(), "hunter.png");

    for (const auto& monster : m_monsters)
        loadTexture(monster.getName(), "enemy.png");

    loadUnlocks();
}

Entity* Codex::findEntity(const std::string& name)
{
    for (Entity& character : m_characters)
        if (character.getName() == name)
            return &character;

    for (Entity& monster : m_monsters)
        if (monster.getName() == name)
            return &monster;

    return nullptr;
}

const Entity* Codex::findEntity(const std::string& name) const
{
    for (const Entity& character : m_characters)
        if (character.getName() == name)
            return &character;

    for (const Entity& monster : m_monsters)
        if (monster.getName() == name)
            return &monster;

    return nullptr;
}

void Codex::markSeen(const std::string& name)
{
    Entity* entity = findEntity(name);
    if (!entity || entity->isUnlocked())
        return;

    entity->Unlock();
    saveUnlocks();
}

bool Codex::isSeen(const std::string& name) const
{
    const Entity* entity = findEntity(name);
    return entity != nullptr && entity->isUnlocked();
}

void Codex::loadUnlocks()
{
    if (m_unlockFile.empty())
        return;

    std::ifstream in(m_unlockFile);
    if (!in)
        return;                       // first run: no save file yet

    std::string line;
    while (std::getline(in, line))
    {
        if (!line.empty() && line.back() == '\r')   // Windows CRLF
            line.pop_back();

        if (line.empty())
            continue;

        if (Entity* entity = findEntity(line))
            entity->Unlock();
    }
}

void Codex::saveUnlocks() const
{
    if (m_unlockFile.empty())
        return;

    std::ofstream out(m_unlockFile, std::ios::trunc);
    if (!out)
    {
        std::cerr << "Codex: cannot write " << m_unlockFile << std::endl;
        return;
    }

    for (const Entity& character : m_characters)
        if (character.isUnlocked())
            out << character.getName() << '\n';

    for (const Entity& monster : m_monsters)
        if (monster.isUnlocked())
            out << monster.getName() << '\n';
}

const sf::Texture& Codex::textureFor(const std::string& name) const
{
    auto it = m_textures.find(name);
    return (it != m_textures.end()) ? it->second : m_fallback;
}
