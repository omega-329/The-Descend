#include "../Header/InventoryState.h"
#include "../Header/Game.h"
#include "../Header/MenuState.h"
#include "../Header/Armor.h"
#include "../Header/Weapon.h"
#include "../Header/Flask.h"
#include <iostream>

InventoryState::InventoryState(Game& game, Player& player, sf::Font& font)
    : game(game), player(player), font(font)
{
    if (!player.getParty().getMembers().empty()) {
        selectedCharIndex = 0;
    }
}

void InventoryState::handleEvent(const sf::Event& event)
{
    if (event.is<sf::Event::KeyPressed>())
    {
        auto code = event.getIf<sf::Event::KeyPressed>()->code;

        if (currentLayer == MenuLayer::LAYER_CHARACTERS)
        {
            if (code == sf::Keyboard::Key::Escape) {
                game.popState();
            }
            else if (code == sf::Keyboard::Key::Down) {
                if (selectedCharIndex < player.getParty().getMembers().size() - 1)
                    selectedCharIndex++;
            }
            else if (code == sf::Keyboard::Key::Up) {
                if (selectedCharIndex > 0)
                    selectedCharIndex--;
            }
            else if (code == sf::Keyboard::Key::Enter) {
                currentLayer = MenuLayer::LAYER_ACTIONS;
                selectedActionIndex = 0;
            }
        }
        else if (currentLayer == MenuLayer::LAYER_ACTIONS)
        {
            if (code == sf::Keyboard::Key::Escape) {
                currentLayer = MenuLayer::LAYER_CHARACTERS;
            }
            else if (code == sf::Keyboard::Key::Down) {
                selectedActionIndex = (selectedActionIndex + 1) % 3;
            }
            else if (code == sf::Keyboard::Key::Up) {
                selectedActionIndex = (selectedActionIndex + 2) % 3;
            }
            else if (code == sf::Keyboard::Key::Enter) {
                if (!getFilteredItems().empty()) {
                    currentLayer = MenuLayer::LAYER_ITEMS;
                    selectedItemIndex = 0;
                }
            }
        }
        else if (currentLayer == MenuLayer::LAYER_ITEMS)
        {
            auto items = getFilteredItems();

            if (code == sf::Keyboard::Key::Escape) {
                currentLayer = MenuLayer::LAYER_ACTIONS;
            }
            else if (code == sf::Keyboard::Key::Down) {
                if (selectedItemIndex < items.size() - 1)
                    selectedItemIndex++;
            }
            else if (code == sf::Keyboard::Key::Up) {
                if (selectedItemIndex > 0)
                    selectedItemIndex--;
            }
            else if (code == sf::Keyboard::Key::Enter) {
                equipOrUseItem(items[selectedItemIndex]);
            }
        }
    }
}


std::vector<Item*> InventoryState::getFilteredItems() const
{
    std::vector<Item*> filtered;
    const auto& allItems = player.getInventory().getItems();

    for (const auto& uPtr : allItems) {
        Item* rawPtr = uPtr.get();

        if (selectedActionIndex == 0 && dynamic_cast<armor*>(rawPtr)) {
            filtered.push_back(rawPtr);
        }
        else if (selectedActionIndex == 1 && dynamic_cast<flasks*>(rawPtr)) {
            filtered.push_back(rawPtr);
        }
        else if (selectedActionIndex == 2 && dynamic_cast<weapons*>(rawPtr)) {
            filtered.push_back(rawPtr);
        }
    }
    return filtered;
}

void InventoryState::equipOrUseItem(Item* item) const
{
    auto& character = player.getParty().getMembers()[selectedCharIndex];

    if (auto* w = dynamic_cast<weapons*>(item)) {
        character.equipWeapon(*w);
        std::cout << "[LOG] " << character.getName() << " equipped " << w->getName() << "!" << std::endl;
    }
    else if (auto* a = dynamic_cast<armor*>(item)) {
        character.equipArmor(*a);
        std::cout << "[LOG] " << character.getName() << " equipped " << a->getName() << "!" << std::endl;
    }
    else if (auto* f = dynamic_cast<flasks*>(item)) {
        float healingAmount = f->interact();

        for (int i = 0; i < character.getLimbCount(); ++i) {
            auto& limb = character.getLimb(i);
            {
                limb.setHP(limb.getHP() + healingAmount);
            }
        }

        std::cout << "[LOG] " << character.getName() << " used " << f->getName()
                  << " and recovered " << healingAmount << " HP!" << std::endl;
    }
}
void InventoryState::draw(sf::RenderWindow& window)
{
    sf::Text title(font,"HUNTING SQUAD", 30);
    title.setPosition({50, 20});
    window.draw(title);

    auto& members = player.getParty().getMembers();

    for (size_t i = 0; i < members.size(); ++i)
    {
        sf::Text nameText(font,members[i].getName(), 24);
        nameText.setPosition({50, 80.f + i * 40});

        if (i == selectedCharIndex) {
            nameText.setFillColor(sf::Color::Yellow);
            nameText.setStyle(sf::Text::Bold);
        } else {
            nameText.setFillColor(sf::Color::White);
        }
        window.draw(nameText);
    }

    if (currentLayer == MenuLayer::LAYER_ACTIONS || currentLayer == MenuLayer::LAYER_ITEMS)
    {
        std::vector<std::string> actions = {"Armor", "Flasks", "Weapons"};

        for (int i = 0; i < 3; ++i) {
            sf::Text actionText(font,actions[i], 24);
            actionText.setPosition({300, 80.f + i * 40});

            if (i == selectedActionIndex && currentLayer >= MenuLayer::LAYER_ACTIONS) {
                if (currentLayer == MenuLayer::LAYER_ITEMS)
                    actionText.setFillColor(sf::Color::Green);
                else
                    actionText.setFillColor(sf::Color::Yellow);
            } else {
                actionText.setFillColor(sf::Color(150, 150, 150));
            }
            window.draw(actionText);
        }
    }

    if (currentLayer == MenuLayer::LAYER_ITEMS)
    {
        auto items = getFilteredItems();

        auto& currentCharacter = player.getParty().getMembers()[selectedCharIndex];

        if (items.empty()) {
            sf::Text emptyText(font, "No items.", 20);
            emptyText.setPosition({500.f, 80.f});
            window.draw(emptyText);
        }

        for (size_t i = 0; i < items.size(); ++i) {
            std::string displayName = items[i]->getName();
            bool isEquipped = false;

            if (auto* w = dynamic_cast<weapons*>(items[i])) {
                if (w->getName() == currentCharacter.getWeapon().getName()) {
                    isEquipped = true;
                }
            }
            else if (auto* a = dynamic_cast<armor*>(items[i])) {
                if (a->getName() == currentCharacter.getArmor().getName()) {
                    isEquipped = true;
                }
            }

            if (isEquipped) {
                displayName += " [E]";
            }

            sf::Text itemText(font, displayName, 24);
            itemText.setPosition({500, 80 + i * 40.f});

            if (i == selectedItemIndex) {
                if (isEquipped) itemText.setFillColor(sf::Color(255, 165, 0));
                else itemText.setFillColor(sf::Color::Yellow);
            }
            else {
                if (isEquipped) itemText.setFillColor(sf::Color::Cyan);
                else itemText.setFillColor(sf::Color::White);
            }

            window.draw(itemText);
        }
    }
}
