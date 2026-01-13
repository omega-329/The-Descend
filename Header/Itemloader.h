

#ifndef OOP_ITEMLOADER_H
#define OOP_ITEMLOADER_H

#pragma once
#include <vector>
#include <memory>
#include <string>
#include "Item.h"

std::vector<std::unique_ptr<Item>> loadItemsFromFile(const std::string& path);

#endif //OOP_ITEMLOADER_H