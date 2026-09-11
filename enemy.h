#pragma once  //I use this instead of #ifndef #define #endif 

#include <string>

#include "GameObject.h"

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

private:
    int health;
    int maxHealth;
    int attackDamage;
};
