

#ifndef OOP_ITEMFACTORY_H
#define OOP_ITEMFACTORY_H
#pragma once
#include <memory>
#include <string>
#include <vector>
#include "Item.h"

class ItemFactory
{
public:
    static std::unique_ptr<Item> create(const std::string& type,const std::vector<std::string>& data);
};

#endif //OOP_ITEMFACTORY_H