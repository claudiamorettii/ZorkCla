#include <iostream>

#include "room.h"

#define RED_ "\033[1;35m"
#define _WHITE "\033[0m"

Room::Room(const std::string& name, const std::string& description) :
    GameObject(name, description, ObjectType::Room)
{
}

void Room::Look() const
{
    std::cout << RED_ "\n=== " << name << " ===\n"  _WHITE;
    std::cout << description << "\n";

    if (exits.empty())
    {
        std::cout << "There are no visible exits.\n";
        return;
    }


    for (const auto& exit : exits)
    {
        std::cout << exit.second.viewDescription;
    }

    std::cout << "You can go:\n";

    for (const auto& exit : exits)
    {
         std::cout << "- " << exit.first << "\n";
    }
}

void Room::AddExit(const std::string& direction, Room* destination, const std::string& viewDescription)
{
    exits[direction] = { destination, viewDescription };
}

Room* Room::GetExit(const std::string& direction) const
{
    auto result = exits.find(direction);

    if (result == exits.end())
    {
        return nullptr;
    }

    return result->second.destination;
}