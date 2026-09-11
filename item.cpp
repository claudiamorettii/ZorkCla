#include <iostream>

#include "item.h"

//--------------------------------------
Item::Item(const string& name, const string& description, ItemType type, bool portable, int damage, int healingAmount):
    GameObject(name, description, ObjectType::Item), itemType(type), portable(portable), damage(damage), healingAmount(healingAmount)
{
}

//--------------------------------------
void Item::Look() const
{
    GameObject::Look();

    if (portable)
    {
        cout << "You can pick it up.\n";
    }
    else 
    {
        cout << "You can't pick it up.\n";
    }
    if (!contents.empty())
    {
        std::cout << "It contains:\n";

        for (const Item* item : contents)
        {
            std::cout << "- " << item->GetName() << '\n';
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