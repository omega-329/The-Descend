
#ifndef OOP_PLAYERINVENTORY_H
#define OOP_PLAYERINVENTORY_H
#pragma once
#include <vector>
#include <memory>
#include "Item.h"

class PlayerInventory
{
public:
    void addItem(std::unique_ptr<Item> item);
    const std::vector<std::unique_ptr<Item>>& getItems() const;

private:
    std::vector<std::unique_ptr<Item>> items;
};
#endif //OOP_PLAYERINVENTORY_H