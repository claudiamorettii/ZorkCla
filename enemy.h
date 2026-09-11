#pragma once  //I use this instead of #ifndef #define #endif 

#include <string>
#include <vector>

#include "GameObject.h"

class Item;

//--------------------------------------
class Enemy : public GameObject
{
public:
    Enemy(const string& name, const string& description, int maxHealth, int attackDamage);

    void Look() const override;
    int GetHealth() const;
    int GetMaxHealth() const;
    bool IsAlive() const;
    void TakeDamage(int amount);
    void AddLoot(Item* item);
    bool HasLoot() const;
    Item* TakeLoot();

private:
    int health;
    int maxHealth;
    int attackDamage;
    vector<Item*> loot;
};
