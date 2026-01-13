#include "../Header/PlayerInventory.h"
void PlayerInventory::addItem(std::unique_ptr<Item> item)
{
    items.push_back(std::move(item));
}

const std::vector<std::unique_ptr<Item>>& PlayerInventory::getItems() const
{
    return items;
}