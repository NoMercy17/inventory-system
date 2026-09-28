#pragma once
#include <string>
#include "Character.hpp"

class DataLoader
{
public:
    static DataLoader& getInstance()
    {
        static DataLoader instance;
        return instance;
    }

    DataLoader(const DataLoader&) = delete;
    DataLoader& operator=(const DataLoader&) = delete;

    Character loadCharacter(const std::string& filename);

private:
    DataLoader() = default;
};