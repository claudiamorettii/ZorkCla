#include <iostream>

#include "player.h"
#include "Room.h"

#define RED_ "\033[1;35m"
#define _WHITE "\033[0m"

Player::Player(const string& name, const string& description, Room* startingRoom) : 
    GameObject(name, description), currentRoom(startingRoom), health(60), maxHealth(100)
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