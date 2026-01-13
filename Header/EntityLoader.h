//
// Created by omega on 10.01.2026.
//

#ifndef OOP_ENTITYLOADER_H
#define OOP_ENTITYLOADER_H
#pragma once
#include <vector>
#include <string>
#include "Entity.h"

std::vector<Entity> loadEntities(const std::string& path);

#endif //OOP_ENTITYLOADER_H