#pragma once //I use this instead of #ifndef #define #endif 

#include <map>
#include <string>
#include <vector>

#include "GameObject.h"


class Item;
class Enemy;

class Room : public GameObject
{
public:

    Room(const string& name, const string& description);
    void Look() const override;
    void AddExit(const string& direction, Room* destination, const string& viewDescription);
    Room* GetExit(const string& direction) const;
    void AddItem(Item* item);
    bool RemoveItem(Item* item);
    Item* FindItem(const string& name) const;
    void ShowExits() const;
    void AddEnemy(Enemy* enemy);
    Enemy* GetEnemy() const;

private:

    struct ExitInfo
    {
        Room* destination;
        string viewDescription;
    };

    vector<Item*> items;
    map <string, ExitInfo> exits;
    vector<Enemy*> enemies;
};