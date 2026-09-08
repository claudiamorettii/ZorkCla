#include <iostream>
#include <sstream>

#include "GameObject.h"
#include "room.h"
#include "game.h"


Game::Game()
    : currentRoom(nullptr),
    running(true)
{
    CreateWorld();
}
void Game::Run()
{

    std::cout << "\nYou slowly open your eyes...\n";
    std::cout << "You cannot remember how you arrived here.\n";

    currentRoom->Look();
     
    while (running)
    {
        std::cout << "\n> ";

        std::string input;
        std::getline(std::cin, input);

        ProcessCommand(input);
    }

    std::cout << "\nThank you for playing ELOS.\n";
}

void Game::ProcessCommand(const std::string& input)
{
    std::istringstream commandStream(input);

    std::string command;
    std::string argument;

    commandStream >> command;
    commandStream >> argument;

    if (command == "look" )
    {
        currentRoom->Look();
    }
    else if (command == "go")
    {
        if (argument.empty())
        {
            std::cout << "Go where?\n";
        }
        else
        {
            Move(argument);
        }
    }
    else if (command == "help")
    {
        ShowHelp();
    }
    else if (command == " Zan")
    {
        running = false;
    }
    else
    {
        std::cout << "I don't understand that command.\n";
    }
}

void Game::Move(const std::string& direction)
{
    Room* destination = currentRoom->GetExit(direction);

    if (destination == nullptr)
    {
        std::cout << "You cannot go in that direction.\nThere is nothing there.";
        return;
    }

    std::cout << "\nYou head\033[1;32m " << direction << "\033[0m...\nAnd arrive at:\n";
    currentRoom = destination;
    currentRoom->Look();
}

void Game::ShowHelp() const
{
    std::cout << "\nAvailable commands:\n";
    std::cout << "- look\n";
    std::cout << "- go north/south/east/west/up/down\n";
    std::cout << "- help\n";
    std::cout << "- quit\n";
}

Room* Game::CreateRoom(
    const std::string& name,
    const std::string& description
)
{
    rooms.push_back(
        std::make_unique<Room>(name, description)
    );

    return rooms.back().get();
}


void Game::CreateWorld()
{
    Room* darkForest = CreateRoom("Dark Forest", "Ancient trees surround you, their twisted branches hiding the sky.");
    Room* clearing = CreateRoom("Forest Clearing", "Moonlight illuminates a small clearing. Something metallic shines beneath the leaves.");
    Room* garden = CreateRoom("Abandoned Garden", "Dead plants cover the garden of an old house.");
    Room* entrance = CreateRoom("House Entrance", "The entrance is cold and silent. Ally, a staircase leads to the upper floor.");
    Room* kitchen = CreateRoom("Kitchen", "Dust covers the kitchen. A strange smell comes from the cupboards.");
    Room* livingRoom = CreateRoom("Living Room", "Broken furniture fills the room. An old parchment rests on a table.");
    Room* basement = CreateRoom("Basement", "The basement is damp and almost completely dark.");
    Room* tunnel = CreateRoom("Underground Tunnel", "A narrow tunnel continues beneath the house.");
    Room* crystalCave = CreateRoom("Crystal Cave", "Glowing crystals illuminate an enormous underground cave.");

    darkForest->AddExit("east", clearing, "To the \033[1;32meast\033[0m, a faint trail leads toward a small clearing.\n");
    clearing->AddExit("west", darkForest, "");

    darkForest->AddExit("south", garden, "Through the drifting fog, you glimpse the remains of an abandoned garden to the \033[1;32msouth\033[0m.\n");
    garden->AddExit("north", darkForest, "");

    garden->AddExit("south", entrance, "");
    entrance->AddExit("north", garden, "");

    entrance->AddExit("east", kitchen, "");
    kitchen->AddExit("west", entrance, "");

    entrance->AddExit("west", livingRoom, "");
    livingRoom->AddExit("east", entrance, "");

    livingRoom->AddExit("down", basement, "");
    basement->AddExit("up", livingRoom, "");

    basement->AddExit("down", tunnel, "");
    tunnel->AddExit("up", basement, "");

    tunnel->AddExit("south", crystalCave, "");
    crystalCave->AddExit("north", tunnel, "");

    currentRoom = darkForest;
}

