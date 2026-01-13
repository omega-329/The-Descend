
#include <fstream>
#include <sstream>
#include <iostream>
#include "../Header/EntityLoader.h"
std::vector<Entity> loadEntities(const std::string& path) {
    std::vector<Entity> entities;
    std::ifstream file(path);
    std::string line;

    while (std::getline(file, line)) {
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string name, desc;
        int limbCount;

        std::getline(ss, name, '|');
        std::getline(ss, desc, '|');
        ss >> limbCount;

        std::vector<Limb> limbs;
        for (int i = 0; i < limbCount; ++i)
        {
            std::getline(file, line);
            std::stringstream limbLine(line);

            float lhp, ldmg;
            std::string limbName;
            limbLine >> limbName >> lhp >> ldmg;
            if (!limbLine) {
                throw std::runtime_error("Malformed limb line: " + line);
            }
            limbs.emplace_back(limbName, lhp, ldmg);
        }
        file.ignore();

        entities.emplace_back(name, desc, limbs);
    }
    return entities;
}