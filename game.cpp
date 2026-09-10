#include <iostream>
#include <sstream>

#include "GameObject.h"
#include "room.h"
#include "game.h"

//--------------------------------------
Game::Game(): 
    currentRoom(nullptr),
    tunnelRoom(nullptr), 
    hasMap(false), //bool for the secret passage that with/o the map does not exist
    passageDiscovered(false),
    running(true)
{
    //all thinghs 
    CreateWorld();

    //player
    player = make_unique<Player>("Player", "You cannot remember how you arrived here.\n", currentRoom);

}

//--------------------------------------
void Game::Run()
{

    cout << "\nYou slowly open your eyes...\n";
    cout << "You cannot remember how you arrived here.\n";

    currentRoom->Look();
     
    while (running)
    {
        cout << "\n> ";

        string input;
        getline(cin, input);

        ProcessCommand(input);
    }
}

//--------------------------------------
//commands to be fixed
void Game::ProcessCommand(const string& input)
{
    istringstream commandStream(input);

    string command;
    string argument;

    commandStream >> command;
    getline(commandStream >> ws, argument);

    if (command == "look")
    {
        if (argument.empty())
        {
            LookAround(); //the one with the if for the map
        }
        else
        {
            LookAtItem(argument);
        }
    }
    else if (command == "go")
    {
        if (argument.empty())
        {
            cout << "Go where?\n";
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
    else if (command == "quit")
    {
        running = false;
    }
    else if (command == "dig")
    {
        Dig();
    }
    else if (command == "take")
    {
        TakeItem(argument);
    }
    else if (command == "drop")
    {
        DropItem(argument);
    }
    else if (command == "inventory")
    {
        player->ShowInventory();
    }
    else
    {
        cout << "I don't understand that command.\n";
    }
}

//--------------------------------------
//tells you where u went with colors
void Game::Move(const string& direction)
{
    Room* destination = currentRoom->GetExit(direction);

    if (destination == nullptr)
    {
        cout << "You cannot go in that direction.\nThere is nothing there.";
        return;
    }

    cout << "\nYou head\033[1;32m " << direction << "\033[0m...\nAnd arrive at:\n";
    currentRoom = destination;
    LookAround();
}

//--------------------------------------
void Game::ShowHelp() const
{
    cout << "\nAvailable commands:\n";
    cout << "- look\n";
    cout << "- go north/south/east/west/up/down\n";
    cout << "- help\n";
    cout << "- quit\n";
}

//--------------------------------------
Room* Game::CreateRoom(
    const string& name,
    const string& description
)
{
    rooms.push_back(make_unique<Room>(name, description));

    return rooms.back().get();
}

//--------------------------------------
void Game::CreateWorld()
{


    //list of rooms
    Room* darkForest = CreateRoom("DARK FOREST", "Ancient trees surround you, their twisted branches hiding the sky.");
    Room* clearing = CreateRoom("FOREST CLEARING", "Moonlight illuminates a small clearing. Something metallic shines beneath the leaves.");
    Room* garden = CreateRoom("ABANDONED GARDEN", "Dead plants cover the garden of an old house.");
    Room* entrance = CreateRoom("HOUSE ENTRANCE", "The entrance is cold and silent. Ally, a staircase leads to the upper floor.");
    Room* kitchen = CreateRoom("KITCHEN", "Dust covers the kitchen. A strange smell comes from the cupboards.");
    Room* livingRoom = CreateRoom("LIVING ROOM", "Broken furniture fills the room.");
    Room* basement = CreateRoom("BASEMENT", "The basement is damp and almost completely dark.");
    Room* tunnel = CreateRoom("UNDERGROUND TUNNEL", "A narrow tunnel continues beneath the house.");
    Room* crystalCave = CreateRoom("CRYSTAL CAVE", "Glowing crystals illuminate an enormous underground cave.");

    //exit.second.viewDescription describe with sentence (addexit and then make the exit around)
    darkForest->AddExit("east", clearing, "To the \033[1;32meast\033[0m, a faint trail leads toward a small clearing.\n");
    clearing->AddExit("west", darkForest, "To the \033[1;32mwest\033[0m, a narrow trail disappears among the ancient trees, leading back into the Dark Forest.\n");

    darkForest->AddExit("south", garden, "Through the drifting fog, you glimpse the remains of an abandoned garden to the \033[1;32msouth\033[0m.\n");
    garden->AddExit("north", darkForest, "To the \033[1;32mnorth\033[0m, an overgrown path disappears beneath the twisted trees of the Dark Forest.\n");

    garden->AddExit("south", entrance, "To the \033[1;32msouth\033[0m, a crumbling stone path leads toward the entrance of the old house.\n");
    entrance->AddExit("north", garden, "Behind you, the front door opens onto the abandoned garden to the \033[1;32mnorth\033[0m.\n");

    entrance->AddExit("east", kitchen, "To the \033[1;32meast\033[0m, a half-open wooden door reveals a dusty kitchen.\n");
    kitchen->AddExit("west", entrance, "To the \033[1;32mwest\033[0m, a wide archway opens into a silent living room.\n");

    entrance->AddExit("west", livingRoom, "To the \033[1;32mwest\033[0m, a wide archway opens into a silent living room.\n");
    livingRoom->AddExit("east", entrance, "To the \033[1;32meast\033[0m, the archway leads back into the entrance hall.\n");

    currentRoom = darkForest; //player starts at dark forest
    clearingRoom = clearing;
    tunnelRoom = tunnel;

    items.push_back(make_unique<Item>("sword", 
        "An old \033[1;33msword\033[0m lies on the ground. Its blade is damaged, but still dangerously sharp.\n", ItemType::Weapon, true));

    clearing->AddItem(items.back().get());

    items.push_back(make_unique<Item>("old map", "You notice an \033[1;33mold map\033[0m, its marked with a red X.\n",ItemType::Map, true));

    livingRoom->AddItem(items.back().get());
}

//--------------------------------------
//dig for the secret passage
void Game::Dig()
{
    if (currentRoom != clearingRoom)
    {
        cout << "You find no reason to dig here.\n";
        return;
    }

    if (!hasMap)
    {
        cout << "You have no idea where to dig.\n";
        return;
    }

    if (passageDiscovered)
    {
        cout << "The hidden passage is already open.\n";
        return;
    }

    passageDiscovered = true;

    clearingRoom->AddExit( "down", tunnelRoom, "Beneath the red X, ancient stone steps descend ""\033[1;32mdown\033[0m into a hidden passage.\n");

    tunnelRoom->AddExit("up", clearingRoom, "Behind you, the stone steps lead " "\033[1;32mup\033[0m to the Forest Clearing.\n");

    cout << "\nYou begin digging beneath the red X.\n"
        << "Beneath the roots, your hands uncover a flat stone slab.\n"
        << "As you push it aside, a staircase descending underground is revealed.\n";

    LookAround();
}

//--------------------------------------
void Game::TakeItem(const string& itemName)
{
    if (itemName.empty())
    {
        cout << "Take what?\n";
        return;
    }

    Item* item = currentRoom->FindItem(itemName);

    if (item == nullptr)
    {
        cout << "There is no " << itemName << " here.\n";
        return;
    }

    if (!item->IsPortable())
    {
        cout << "You cannot take that.\n";
        return;
    }

    currentRoom->RemoveItem(item);
    player->AddItem(item);

    cout
        << "You pick up the \033[1;33m" << item->GetName() << "\033[0m.\n";

    if (item->GetItemType() == ItemType::Map)
    {
        hasMap = true;
        cout << "You can look at the \033[1;33mold map\033[0m now!\n";
    }
}

//--------------------------------------
void Game::DropItem(const string& itemName)
{
    if (itemName.empty())
    {
        cout << "Drop what?\n";
        return;
    }

    Item* item = player->FindItem(itemName);

    if (item == nullptr)
    {
        cout << "You are not carrying " << itemName << ".\n";
        return;
    }

    player->RemoveItem(item);
    currentRoom->AddItem(item); //drop the item in that room

    cout
        << "You drop the \033[1;33m" << item->GetName() << "\033[0m.\n";

    if (item->GetItemType() == ItemType::Map)
    {
        hasMap = false;
    }
}

//--------------------------------------
void Game::LookAround() const
{
    currentRoom->Look();

    if (currentRoom == clearingRoom && hasMap && !passageDiscovered)
    {
        cout << "\nAs you compare the clearing with the old map, you notice that the red X matches a patch of disturbed soil.\n"
            << "Perhaps you should \033[1;33mdig\033[0m here.\n";
    }

    currentRoom->ShowExits();
}

//--------------------------------------
//only if the player hasMAp
void Game::ShowMap() const
{
    if (!hasMap)
    {
        cout << "You don't have a map.\n";
        return;
    }

    cout << R"MAP(
+========================================================+
|                                                        |
|                   * MAP OF ELOS *                      |
|                                                        |
|      ^  ^  ^  ^  ^                                     |
|    ^               ^        .----------------.         |
|   ^   DARK FOREST   ^-------| FOREST CLEARING|         |
)MAP"

<< "|    ^               ^        |       \033[1;31mX\033[0m        |"  // had to do like this cause in the R"MAP i can't use colors

<< R"MAP(         |
|      ^  ^  ^  ^  ^          '-------+--------'         |
|             |                       :                  |
|       .-----+------.                :                  |
|       |  ABANDONED |                :                  |
|       |   GARDEN   |                :                  |
|       '-----+------'                :                  |
|             |                       : Hidden path      |
|            / \                      :                  |
|          /     \                    :                  |
|        /         \                  :                  |
|       |-----------|                 :                  |
|       | OLD HOUSE |                 :                  |
|       |-----------|                 :                  |
|       | (KITCHEN) |                 :                  |
|       '-----------'                 :                  |
|            |                        :                  |
|        +---+---------+              :                  |
|        |  BASEMENT   |              :                  |
|        +-------------+              :                  |
|                                .----+----.             |
|                               /   DARK    \            |
|                              /   PASSAGE   \           |
|                              '------+------'           |
|                                     |                  |
|                              * * * * * * * *           |
|                            *  CRYSTAL CAVE  *          |
|                              * * * * * * * *           |
|                                                        |
|      X = Something is buried here                      |
|      : = Hidden path                                   |
|                                                        |
+========================================================+

)MAP";
}

//--------------------------------------
void Game::LookAtItem(const string& itemName) const
{
    Item* item = player->FindItem(itemName);
    bool isInInventory = item != nullptr;

    if (item == nullptr)
    {
        item = currentRoom->FindItem(itemName);
    }

    if (item == nullptr)
    {
        cout << "You cannot see an item called " << itemName << ".\n";
        return;
    }

    item->Look();

    if (item->GetItemType() == ItemType::Map)
    {
        if (isInInventory)
        {
            ShowMap();
        }
        else
        {
            cout << "The parchment is too fragile to examine from here.\n";
        }
    }
} 
