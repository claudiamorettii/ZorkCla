#include <iostream>

#include "item.h"

//--------------------------------------
Item::Item(const string& name, const string& description, ItemType type, bool portable, int damage):
    GameObject(name, description, ObjectType::Item), itemType(type), portable(portable), damage(damage)
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