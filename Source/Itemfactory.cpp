
#include "../Header/ItemFactory.h"
#include "../Header/Weapon.h"
#include "../Header/Armor.h"
#include "../Header/Flask.h"
#include <stdexcept>

std::unique_ptr<Item> ItemFactory::create(const std::string& type,const std::vector<std::string>& data)
{
    if (type == "weapon")
    {
        float dmg  = std::stof(data[0]);
        float miss = std::stof(data[1]);
        return std::make_unique<weapons>(
            dmg, miss, data[2], data[3]);
    }
    else if (type == "armor")
    {
        float red = std::stof(data[0]);
        return std::make_unique<armor>(
            red, data[1], data[2]);
    }
    else if (type == "flask")
    {
        float dmg = std::stof(data[0]);
        float heal = std::stof(data[1]);
        float armor = std::stof(data[2]);
        return std::make_unique<flasks>(
            dmg, heal,armor,  data[3], data[4]);
    }

    throw std::runtime_error("Unknown item type: " + type);
}