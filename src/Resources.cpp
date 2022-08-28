#include "Resources.hpp"
#include <iostream>
#include <dirent.h>

bool Resources::load(const std::string &directory) {
    struct dirent *entry;
    std::string dirString = directory + std::string("sprites/items/");
    DIR *dir = opendir(dirString.c_str());

    if (dir == nullptr) {
        return false;
    }
    std::cout << std::endl;
    while ((entry = readdir(dir)) != nullptr) {
        std::string name = entry->d_name;
        size_t lastIndex = name.find_first_of('.');
        std::string rawName = name.substr(0, lastIndex);
        if (rawName.length() != 0) {
            std::cout << rawName << std::endl;
            if (!textures[rawName].loadFromFile(dirString + name)) {
                std::cout << rawName << " failed to load!" << std::endl;
                return false;
            }
        }
    }
    closedir(dir);

    if (!fonts["tahoma"].loadFromFile(directory + std::string("TAHOMA_0.TTF")))
    {
        // error...
        printf("failed to load font TAHOMA_0.TTF\n");
        return false;
    }

    return true;
}
