#pragma once

#include <string>
#include <vector>

#include "GameObject.h"
#include "room.h"

class Room;
class Item;

//--------------------------------------
//player is difine like a gameobject
class Player : public GameObject
{
public:
    Player(const string& name, const string& description, Room* startingRoom);

    Room* GetCurrentRoom() const;

    int GetHealth() const;
    int GetMaxHealth() const;
    bool IsAlive() const;
    void TakeDamage(int amount);
    void Heal(int amount);
    bool AddItem(Item* item);
    bool RemoveItem(Item* item);
    Item* FindItem(const std::string& name) const;
    void ShowInventory() const;

private:

    Room* currentRoom;
    int health;
    int maxHealth;
    vector<Item*> inventory;
};
