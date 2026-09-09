#include "Item.h"

#include <iostream>

Item::Item(const string& name, const string& description, ItemType type, bool portable): 
    GameObject(name, description, ObjectType::Item), itemType(type), portable(portable)
{
}

void Item::Look() const
{
    GameObject::Look();

    if (portable)
    {
        cout << "You can pick it up.\n";
    }
}

ItemType Item::GetItemType() const
{
    return itemType;
}

bool Item::IsPortable() const
{
    return portable;
}