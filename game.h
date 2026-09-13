#pragma once //I use this instead of #ifndef #define #endif 
#include <memory>
#include <string>
#include <algorithm>

#include "room.h"
#include "item.h"
#include "player.h"
#include "enemy.h"

using namespace std;

class Game
{
public:
    Game();

    void Run();

private:
    vector<unique_ptr<Room>> rooms;
    vector<unique_ptr<Item>> items;
    Room* currentRoom;
    bool running;
    Room* clearingRoom;
    Room* tunnelRoom;
    Room* basementRoom;
    bool basementUnlocked;
    bool hasMap;
    bool passageDiscovered;
    Room* crystalCaveRoom;

    void ShowMap() const;
    void Dig();
    void CreateWorld();
    Room* CreateRoom(const string& name, const string& description);
    void LookAround() const;
    void ProcessCommand(const string& input);
    void Move(const string& direction);
    void ShowHelp() const;
    void TakeItem(const string& itemName);
    void DropItem(const string& itemName);
    void UnequipItem(const string& itemName);
    void EatItem(const string& itemName);
    void LookAtItem(const string& itemName) const;
    void EquipItem(const string& itemName);
    void PutItem(const string& arguments);
    bool HasWorkingFlashlight() const;
    void AttackEnemy(const string& enemyName);
    void LootEnemy();
    void TalkToEnemy(const string& enemyName);

    void FinishGame();
    
    unique_ptr<Player> player;
    vector<unique_ptr<Enemy>> enemies;
};

