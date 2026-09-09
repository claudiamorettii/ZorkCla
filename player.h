#pragma once

#include <string>

#include "GameObject.h"
#include "room.h"

class Room;

class Player : public GameObject
{
public:
    Player(
        const string& name,
        const string& description,
        Room* startingRoom
    );

    Room* GetCurrentRoom() const;

    int GetHealth() const;
    int GetMaxHealth() const;
    bool IsAlive() const;

    void TakeDamage(int amount);
    void Heal(int amount);

private:
    Room* currentRoom;

    int health;
    int maxHealth;
};
