#pragma once //I use this instead of #ifndef #define #endif 

#include <string>
#include <vector>

#include "GameObject.h"

//--------------------------------------
//item divided so is easier to classify them 
enum class ItemType
{
    Generic,
    Weapon,
    Food,
    Key,
    Map,
    Flashlight,
    Battery,
    Crystal,
    Container
};

//--------------------------------------
class Item : public GameObject
{
public:
    Item(const string& name, const string& description, ItemType type, bool portable, int damage = 0, int healingAmount = 0);

    void Look() const override;
    ItemType GetItemType() const;
    bool IsPortable() const;
    int GetDamage() const;
    int GetHealingAmount() const;
    bool CanContainItems() const;
    bool AddContent(Item* item);
    bool ContainsItemType(ItemType type) const;

    //for the berries
    int GetQuantity() const;
    void SetQuantity(int amount);
    bool ConsumeOne();

private:
    ItemType itemType;
    bool portable;
    int damage;
    int healingAmount;
    vector<Item*> contents;


    int quantity;
    int harmChance;
    int harmDamage;
};
