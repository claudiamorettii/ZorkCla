#pragma once

#include <memory>
#include <string>
#include <vector>

#include "room.h"

class Game
{
public:
    Game();

    void Run();

private:
    vector<unique_ptr<Room>> rooms;
    Room* currentRoom;
    bool running;

    void CreateWorld();

    Room* CreateRoom(const string& name, const string& description);

    void ProcessCommand(const string& input);
    void Move(const string& direction);
    void ShowHelp() const;
};

