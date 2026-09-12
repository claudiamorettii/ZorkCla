#pragma once  //I use this instead of #ifndef #define #endif 

#include <string>
#include <vector>

#include "GameObject.h"

class Item;

//--------------------------------------
class Enemy : public GameObject
{
public:
    Enemy(const string& name, const string& description, int maxHealth, int attackDamage, bool startsHostile = true);

    void Look() const override;
    int GetHealth() const;
    int GetMaxHealth() const;
    bool IsAlive() const;
    void TakeDamage(int amount);
    void AddLoot(Item* item);
    bool HasLoot() const;
    Item* TakeLoot();
    bool IsHostile() const;
    bool HasSpoken() const;
    void SetHostile(bool value);
    void SetHasSpoken(bool value);
    bool HasBeenAttacked() const;
    void SetHasBeenAttacked(bool value);
    bool HasSolvedRiddle() const;
    void SetRiddleSolved(bool value);

private:
    int health;
    int maxHealth;
    int attackDamage;
    bool hasBeenAttacked;
    bool hostile;
    bool hasSpoken;
    bool riddleSolved;
    vector<Item*> loot;
};
