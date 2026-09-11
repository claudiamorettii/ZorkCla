#include <iostream>
#include <algorithm>

#include "player.h"
#include "Room.h"
#include "item.h"
#include "GameObject.h"

using namespace std; 

Player::Player(const string& name, const string& description, Room* startingRoom) : 
    GameObject(name, description, ObjectType::Player), 
    currentRoom(startingRoom), 
    health(60),
    maxHealth(100), 
    equippedWeapon(nullptr)
{
}

//--------------------------------------
//get where the player is
Room* Player::GetCurrentRoom() const
{
    return currentRoom;
}

//--------------------------------------
int Player::GetHealth() const
{
    return health;
}

//--------------------------------------
int Player::GetMaxHealth() const
{
    return maxHealth;
}

//--------------------------------------
bool Player::IsAlive() const
{
    return health > 0;
}

//--------------------------------------
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

//--------------------------------------
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

//--------------------------------------
bool Player::Equip(Item* item)
{
    if (item == nullptr)
    {
        return false;
    }

    if (item->GetItemType() != ItemType::Weapon)
    {
        return false;
    }

    equippedWeapon = item;
    return true;
}

//--------------------------------------
void Player::Unequip()
{
    equippedWeapon = nullptr;
}

//--------------------------------------
Item* Player::GetEquippedWeapon() const
{
    return equippedWeapon;
}

//--------------------------------------
int Player::GetAttackDamage() const
{
    const int baseDamage = 2;

    if (equippedWeapon == nullptr)
    {
        return baseDamage;
    }

    return baseDamage + equippedWeapon->GetDamage();
}

//--------------------------------------
//take and put in the backpack
bool Player::AddItem(Item* item)
{
    if (item == nullptr)
    {
        return false;
    }

    inventory.push_back(item);
    return true;
}

//--------------------------------------
//drop (the position is in game.cpp)
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

//--------------------------------------
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

//--------------------------------------
//look in the backpack
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