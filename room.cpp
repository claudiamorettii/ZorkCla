#include <iostream>

#include "room.h"

#define RED_ "\033[1;35m"
#define _WHITE "\033[0m"

Room::Room(const string& name, const string& description) :
    GameObject(name, description, ObjectType::Room)
{
}

void Room::Look() const
{
    cout << RED_ "\n=== " << name << " ===\n"  _WHITE;
    cout << description << "\n";

    if (exits.empty())
    {
        cout << "There are no visible exits.\n";
        return;
    }


    for (const auto& exit : exits)
    {
        cout << exit.second.viewDescription;
    }

    cout << "You can go:\n";

    for (const auto& exit : exits)
    {
         cout << "- " << exit.first << "\n";
    }
}

void Room::AddExit(const string& direction, Room* destination, const string& viewDescription)
{
    exits[direction] = { destination, viewDescription };
}

Room* Room::GetExit(const string& direction) const
{
    auto result = exits.find(direction);

    if (result == exits.end())
    {
        return nullptr;
    }

    return result->second.destination;
}