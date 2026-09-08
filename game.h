#pragma once

#include <memory>
#include <string>
#include <vector>

#include "Room.h"

class Game
{
public:
    Game();

    void Run();

private:
    std::vector<std::unique_ptr<Room>> rooms;
    Room* currentRoom;
    bool running;

    void CreateWorld();

    Room* CreateRoom(const std::string& name, const std::string& description);

    void ProcessCommand(const std::string& input);
    void Move(const std::string& direction);
    void ShowHelp() const;
};

