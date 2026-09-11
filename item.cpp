#include <iostream>


#include "item.h"
#include "enemy.h"
#include "room.h"
#include "game.h"

//--------------------------------------
Item::Item(const string& name, const string& description, ItemType type, bool portable, int damage, int healingAmount):
    GameObject(name, description, ObjectType::Item),
    itemType(type), 
    portable(portable), 
    damage(damage),
    healingAmount(healingAmount),
    quantity(1),
    harmChance(0),
    harmDamage(0)
{
}

//--------------------------------------
void Item::Look() const
{
    GameObject::Look();
        
    if (!contents.empty())
    {
        cout << "It contains:\n";

        for (const Item* item : contents)
        {
            cout << "- " << item->GetName() << '\n';
        }
    }
}

//--------------------------------------
ItemType Item::GetItemType() const
{
    return itemType;
}

//--------------------------------------
bool Item::IsPortable() const
{
    return portable;
}

//--------------------------------------
int Item::GetDamage() const
{
    return damage;
}

//--------------------------------------
int Item::GetHealingAmount() const
{
    return healingAmount;
}

//--------------------------------------
bool Item::CanContainItems() const
{
    return itemType == ItemType::Container || itemType == ItemType::Flashlight;
}

//--------------------------------------
bool Item::AddContent(Item* item)
{
    if (item == nullptr || !CanContainItems())
    {
        return false;
    }

    contents.push_back(item);
    return true;
}

//--------------------------------------
bool Item::ContainsItemType(ItemType type) const
{
    for (const Item* item : contents)
    {
        if (item->GetItemType() == type)
        {
            return true;
        }
    }

    return false;
}

//--------------------------------------
//For the berries
int Item::GetQuantity() const
{
    return quantity;
}

//--------------------------------------
//For the berries
void Item::SetQuantity(int amount)
{
    if (amount > 0)
    {
        quantity = amount;
    }
}

//--------------------------------------
//For the berries
bool Item::ConsumeOne()
{
    if (quantity <= 0)
    {
        return false;
    }

    --quantity;
    return true;
}