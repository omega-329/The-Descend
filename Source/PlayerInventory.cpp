#include "../Header/PlayerInventory.h"
#include <algorithm>

void PlayerInventory::addItem(std::unique_ptr<Item> item)
{
    items.push_back(std::move(item));
}
const std::vector<std::unique_ptr<Item>>& PlayerInventory::getItems() const
{
    return items;
}
std::vector<Item*> PlayerInventory::getConsumables() const
{
    std::vector<Item*> consumables;
    consumables.reserve(items.size());
    for (const auto& uPtr : items) {
        if (uPtr->isConsumable()) {
            consumables.push_back(uPtr.get());
        }
    }
    return consumables;
}
bool PlayerInventory::consume(Item* item)
{
    for (auto it = items.begin(); it != items.end(); ++it) {
        if (it->get() == item) {
            it->get()->decreaseQuantity();
            if (it->get()->getQuantity() <= 0) {
                items.erase(it);
                return true;
            }
            return false;
        }
    }
    return false;
}
