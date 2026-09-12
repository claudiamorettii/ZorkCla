#include <iostream>
#include <algorithm>

#include "room.h"
#include "item.h"
#include "game.h"
#include "enemy.h"

//--------------------------------------
Room::Room(const string& name, const string& description) :
    GameObject(name, description, ObjectType::Room)
{
}

//--------------------------------------
void Room::Look() const
{
    cout <<  "\033[1;35m\n=== " << name << " ===\n\033[0m";
    cout << description << "\n";

    //no exit
    if (exits.empty())
    {
        cout << "There are no visible exits.\n";
        return;
    }


    for (const auto& exit : exits)
    {
        cout << exit.second.viewDescription; //second is the line I add for telling the position with a sentence
    }

    if (!items.empty()) //items in the rooms
    {
        for (const Item* item : items)
        {
           cout << item->GetDescription(); //print the description of the item
        }
    }

    if (!enemies.empty())
    {
       
        for (const Enemy* enemy : enemies)
        {
            if (enemy->IsAlive())
            {
                cout << enemy->GetDescription();
                cout << enemy->GetName() << " health: " << enemy->GetHealth() << "/" << enemy->GetMaxHealth() << "\n";
            }
            else
            {
                cout << "The corpse of a \033[1;31m" << enemy->GetName() << "\033[0m" " lies on the ground.\n";
            }
        }
    }
}

//--------------------------------------
Enemy* Room::GetEnemy() const
{
    if (enemies.empty())
    {
        return nullptr;
    }

    return enemies.front();
}

//--------------------------------------
void Room::ShowExits() const
{
    if (exits.empty())
    {
        cout << "\nThere are no visible exits.\n";
        return;
    }

    cout << "\nYou can go:\n";

    for (const auto& exit : exits)
    {
        cout << "- " << exit.first << "\n"; //where u can go with colors
    }
}

//--------------------------------------
void Room::AddExit(const string& direction, Room* destination, const string& viewDescription)
{
    exits[direction] = {destination, viewDescription};
}

//--------------------------------------
Room* Room::GetExit(const string& direction) const
{
    auto result = exits.find(direction);

    if (result == exits.end())
    {
        return nullptr;
    }

    return result->second.destination; 
}

//--------------------------------------
void Room::AddItem(Item* item)
{
    if (item != nullptr)
    {
        items.push_back(item);
    }
}

//--------------------------------------
bool Room::RemoveItem(Item* item)
{
    auto result = find(
        items.begin(),
        items.end(),
        item
    );

    if (result == items.end())
    {
        return false;
    }

    items.erase(result);
    return true;
}

//--------------------------------------
Item* Room::FindItem(const string& name) const
{
    for (Item* item : items)
    {
        
        string currentName = item->GetName();

        transform(currentName.begin(), currentName.end(), currentName.begin(), [](unsigned char character)
            {
                return static_cast<char>(tolower(character));
            });

       
        if (currentName == name)
        {
            return item;
        }
    }

    return nullptr;
}

//--------------------------------------
void Room::AddEnemy(Enemy* enemy)
{
    if (enemy != nullptr)
    {
        enemies.push_back(enemy);
    }
}
