#include <iostream>
#include <algorithm>

#include "player.h"
#include "Room.h"
#include "item.h"
#include "GameObject.h"

using namespace std; 

Player::Player(const string& name, const string& description, Room* startingRoom) : 
    GameObject(name, description, ObjectType::Player), currentRoom(startingRoom), health(60), maxHealth(100)
{
}

Room* Player::GetCurrentRoom() const
{
    return currentRoom;
}
int Player::GetHealth() const
{
    return health;
}

int Player::GetMaxHealth() const
{
    return maxHealth;
}

bool Player::IsAlive() const
{
    return health > 0;
}

void Player::TakeDamage(int amount)
{
    if (amount <= 0)
    {
        return;
    }

    health -= amount;

    if (health < 0)
    {
        health = 0;
    }
}

void Player::Heal(int amount)
{
    if (amount <= 0)
    {
        return;
    }

    health += amount;

    if (health > maxHealth)
    {
        health = maxHealth;
    }
}

bool Player::AddItem(Item* item)
{
    if (item == nullptr)
    {
        return false;
    }

    inventory.push_back(item);
    return true;
}

bool Player::RemoveItem(Item* item)
{
    auto result = find(inventory.begin(), inventory.end(), item);

    if (result == inventory.end())
    {
        return false;
    }

    inventory.erase(result);
    return true;
}

Item* Player::FindItem(const std::string& name) const
{
    for (Item* item : inventory)
    {
        if (item->GetName() == name)
        {
            return item;
        }
    }

    return nullptr;
}

void Player::ShowInventory() const
{
   
    if (inventory.empty())
    {
        cout << "\nYour backpack is empty.\n";
        return;
    }

    cout << "\nIn your \033[1mbackpack\033[0m you have:\n";

    for (const Item* item : inventory)
    {
        cout
            << "- "
            << item->GetName()
            << '\n';
    }
}