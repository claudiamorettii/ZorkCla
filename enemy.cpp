#include <iostream>

#include "enemy.h"
#include "item.h"

//--------------------------------------
Enemy::Enemy(const string& name, const string& description, int maxHealth, int attackDamage): 
      GameObject(name, description, ObjectType::Enemy),
      health(maxHealth),
      maxHealth(maxHealth),
      attackDamage(attackDamage)
{
}

//--------------------------------------
void Enemy::Look() const
{
    GameObject::Look();

    if (IsAlive())
    {
        cout << "Health: " << health << "/" << maxHealth << "\n";
    }
    else
    {
        cout << "The enemy is dead.\n";
    }
}

//--------------------------------------
int Enemy::GetHealth() const
{
    return health;
}

//--------------------------------------
int Enemy::GetMaxHealth() const
{
    return maxHealth;
}

//--------------------------------------
bool Enemy::IsAlive() const
{
    return health > 0;
}

//--------------------------------------
void Enemy::TakeDamage(int amount)
{
    if (amount <= 0 || !IsAlive())
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
void Enemy::AddLoot(Item* item)
{
    if (item != nullptr)
    {
        loot.push_back(item);
    }
}

//--------------------------------------
bool Enemy::HasLoot() const
{
    return !loot.empty();
}

//--------------------------------------
Item* Enemy::TakeLoot()
{
    if (loot.empty())
    {
        return nullptr;
    }

    Item* item = loot.back();
    loot.pop_back();

    return item;
}