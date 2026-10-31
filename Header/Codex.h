#ifndef OOP_CODEX_H
#define OOP_CODEX_H
#pragma once

#include <map>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Entity.h"

// Persistent catalogue of everything the player can look up.
// It owns the entity data and one texture per entity, and it lives in Game,
// so it outlives every state (menu, combat, game over...).
//
// The "seen" flag lives on Entity::unlocked, and every unlock is persisted to
// a small text file so the codex survives closing the game.
class Codex
{
public:
    void load(const std::string& entitiesFile,
              const std::string& spriteDir,
              const std::string& unlockFile);

    [[nodiscard]] const std::vector<Entity>& characters() const { return m_characters; }
    [[nodiscard]] const std::vector<Entity>& monsters() const { return m_monsters; }

    // Unlocks the entity (monster or hunter) with this name and writes the save file.
    void markSeen(const std::string& name);
    [[nodiscard]] bool isSeen(const std::string& name) const;

    // Never returns an invalid reference: if the file is missing we fall back
    // to a generic texture (or an empty one, which the caller must not draw).
    const sf::Texture& textureFor(const std::string& name) const;

private:
    Entity* findEntity(const std::string& name);
    const Entity* findEntity(const std::string& name) const;

    void loadUnlocks();
    void saveUnlocks() const;

    std::vector<Entity> m_characters;
    std::vector<Entity> m_monsters;

    // std::map keeps its nodes stable, so references returned by textureFor()
    // stay valid even if we add more entries later.
    std::map<std::string, sf::Texture> m_textures;
    sf::Texture m_fallback;

    std::string m_unlockFile;
};

#endif //OOP_CODEX_H
