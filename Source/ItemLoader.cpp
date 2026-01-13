#include "../Header/ItemFactory.h"
#include "../Header/ItemLoader.h"
#include <fstream>
#include <sstream>

std::vector<std::unique_ptr<Item>> loadItemsFromFile(const std::string& path)
{
    std::vector<std::unique_ptr<Item>> items;
    std::ifstream file(path);

    std::string line;
    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string type;
        std::getline(ss, type, ',');

        std::vector<std::string> data;
        std::string token;
        while (std::getline(ss, token, ','))
            data.push_back(token);

        items.push_back(ItemFactory::create(type, data));
    }

    return items;
}