#pragma once

#include "GameObject.h"

#include <string>

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

class Item : public GameObject
{
public:
    Item(const string& name, const string& description, ItemType type, bool portable);

    void Look() const override;
    ItemType GetItemType() const;
    bool IsPortable() const;

private:
    ItemType itemType;
    bool portable;
};
