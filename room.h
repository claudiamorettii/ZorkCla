#pragma once //I use this instead of #ifndef #define #endif 

#include <map>
#include <string>
#include <vector>

#include "GameObject.h"

class Item;

class Room : public GameObject
{
public:

    Room(const string& name, const string& description);
    void Look() const override;
    void AddExit(const string& direction, Room* destination, const string& viewDescription);
    Room* GetExit(const string& direction) const;
    void AddItem(Item* item);
    bool RemoveItem(Item* item);
    Item* FindItem(const std::string& name) const;
    void ShowExits() const;


private:

    struct ExitInfo
    {
        Room* destination;
        string viewDescription;
    };

    vector<Item*> items;
    map <string, ExitInfo> exits;
};