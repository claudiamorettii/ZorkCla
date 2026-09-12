#include <iostream>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <random> //for the berries

#include "GameObject.h"
#include "room.h"
#include "game.h"
#include "player.h"
#include "enemy.h"

//--------------------------------------
//for the random berries
namespace
{
    int RandomBetween(int minimum, int maximum)
    {
        static random_device randomDevice;
        static mt19937 generator(randomDevice()); //the ranodm numbers
        uniform_int_distribution<int> distribution(minimum, maximum);

        return distribution(generator);
    }
}

//--------------------------------------
Game::Game(): 
    currentRoom(nullptr),
    tunnelRoom(nullptr), 
    basementUnlocked(false),
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
    cout << "You cannot remember how you arrived here in\n";

    LookAround();
     
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
    string normalizedInput = input;

    transform(normalizedInput.begin(), normalizedInput.end(), normalizedInput.begin(),[](unsigned char character)
        {
            return static_cast<char>(tolower(character));
        }
    );

    istringstream commandStream(normalizedInput);

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
    else if (command == "take" || command == "pick")
    {
        TakeItem(argument);
    }
    else if (command == "drop" || command == "leave")
    {
        DropItem(argument);
    }
    else if (command == "eat")
    {
        EatItem(argument);
    }
    else if (command == "health")
    {
        cout << "\nYour health: " << player->GetHealth() << "/" << player->GetMaxHealth() << "\n";
    }
    else if (command == "equip")
    {
        EquipItem(argument);
    }
    else if (command == "attack")
    {
        AttackEnemy(argument);
    }
    else if (command == "talk to" || command == "talk")
    {
        TalkToEnemy(argument);
    }
    else if (command == "loot")
    {
        LootEnemy();
    }
    else if (command == "inventory" || command == "backpack" || command == "i")
    {
        player->ShowInventory();
    }
    else if (command == "put")
    {
        PutItem(argument);
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
        cout << "You cannot go in that direction.\n";
        return;
    }

    cout << "\n---------------------------------------------------------------------\n\n";

    if (destination == basementRoom && !basementUnlocked)
    {
        Item* basementKey = player->FindItem("basement key");

        if (basementKey == nullptr)
        {
            cout << "The basement door is locked.\n";
            cout << "A large iron keyhole is set beneath the handle.\n";
            return;
        }

        basementUnlocked = true;

        cout << "You insert the \033[1;33mBasement Key\033[0m into the lock.\n";
        cout << "With a loud metallic click, the basement door opens.\n";
    }

    if (destination == tunnelRoom && !HasWorkingFlashlight() //only with flashligh
        )
    {
        cout << "The passage is completely dark.\nYou hear something moving below, but you cannot see it.\n"
            << "You need a working \033[1;33mflashlight\033[0m before going down.\n";

        return;
    }

    
    cout << "You head " << direction << "...\n";

    Enemy* enemy = currentRoom->GetEnemy();

    if (currentRoom == tunnelRoom && destination == crystalCaveRoom &&
        enemy != nullptr && enemy->IsAlive())
    {
        cout << "The \033[1;31mCave Guardian\033[0m moves in front of the passage.\n";
        cout << "\033[1;31mYou cannot reach the Crystal Cave while it is still alive.\033[0m\n";
        cout << "You must fight it or retreat.\n";
        return;
    }

    if (enemy != nullptr && enemy->IsAlive())//if you pass the enemy withput the fight
    {
        cout
            << "You carefully move around the \033[1;31m" << enemy->GetName() 
            << "\033[0m, keeping a safe distance.\n" << "For now, you manage to avoid the fight.\n";
    }
    
    cout << "And arrive at:\n";
    currentRoom = destination;
    LookAround();
}

//--------------------------------------
void Game::ShowHelp() const
{
    cout << "\nAvailable commands:\n";
    cout << "- look\n";
    cout << "- look ...\n";
    cout << "- go north/south/east/west/up/down\n";
    cout << "- take/pick\n";
    cout << "- drop/leave\n";
    cout << "- eat ...\n";
    cout << "- equip\n";
    cout << "- attack\n";
    cout << "- talk to\n";
    cout << "- inventory/backpack\n";
    cout << "- dig\n";
    cout << "- put\n";
    cout << "- health\n";
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
    Room* clearing = CreateRoom("FOREST CLEARING", "Moonlight illuminates a small clearing.");
    Room* garden = CreateRoom("ABANDONED GARDEN", "Dead plants cover the garden of an old house.");
    Room* entrance = CreateRoom("HOUSE ENTRANCE", "The entrance is cold and silent.");
    Room* kitchen = CreateRoom("KITCHEN", "Dust covers the kitchen. A strange smell comes from the cupboards.");
    Room* livingRoom = CreateRoom("LIVING ROOM", "Broken furniture fills the room.");
    Room* basement = CreateRoom("BASEMENT", "Cold, damp air fills the basement. Dusty shelves line the stone walls, and a rusted toolbox lies in a dark corner.");
    Room* tunnel = CreateRoom("UNDERGROUND TUNNEL", "A narrow tunnel  almost completely dark.");
    Room* crystalCave = CreateRoom("CRYSTAL CAVE", "Thousands of \033[1;36mcrystals\033[0m rise from the stone, scattering the flashlight's beam into shifting colors.\n"
                                   "At the center of the cave, an ancient crystal rests upon a stone pedestal.");

    //exit.second.viewDescription describe with sentence (addexit and then make the exit around)
    darkForest->AddExit("east", clearing, "To the \033[1;32meast\033[0m, a faint trail leads toward a small clearing.\n");
    clearing->AddExit("west", darkForest, "To the \033[1;32mwest\033[0m, a narrow trail disappears among the ancient trees, leading back into the Dark Forest.\n");

    darkForest->AddExit("south", garden, "Through the drifting fog, you glimpse the remains of an abandoned garden to the \033[1;32msouth\033[0m.\n");
    garden->AddExit("north", darkForest, "To the \033[1;32mnorth\033[0m, an overgrown path disappears beneath the twisted trees of the Dark Forest.\n");

    garden->AddExit("south", entrance, "To the \033[1;32msouth\033[0m, a crumbling stone path leads toward the entrance of the old house.\n");
    entrance->AddExit("north", garden, "Behind you, the front door opens onto the abandoned garden to the \033[1;32mnorth\033[0m.\n");

    entrance->AddExit("east", kitchen, "To the \033[1;32meast\033[0m, a half-open wooden door reveals a dusty kitchen.\n");
    kitchen->AddExit("west", entrance, "A wide archway  leads \033[1;32mwest\033[0m to the Living Room.\n");

    entrance->AddExit("west", livingRoom, "To the \033[1;32mwest\033[0m, a wide archway opens into a silent living room.\n");
    livingRoom->AddExit("east", entrance, "A narrow wooden staircase leads \033[1;32mdown\033[0m to the basement.\n"); 

    livingRoom->AddExit("down", basement, "To the \033[1;32meast\033[0m, the archway leads back into the entrance hall.\n");
    basement->AddExit("up", livingRoom, "A narrow wooden staircase leads \033[1;32mup\033[0m to the living Room.\n");

    tunnel->AddExit("south", crystalCave, "Beyond the creature, a pale blue light shines to the \033[1;32msouth\033[0m.\n");
    crystalCave->AddExit("north", tunnel, "The dark tunnel waits behind you to the \033[1;32mnorth\033[0m.\n");

    currentRoom = darkForest; //player starts at dark forest
    clearingRoom = clearing;
    basementRoom = basement;
    tunnelRoom = tunnel;
    crystalCaveRoom = crystalCave;

    //creation item
    items.push_back(make_unique<Item>("Sword", 
        "An old \033[1;33msword\033[0m lies on the ground. Its blade is damaged, but still dangerously sharp.\n", ItemType::Weapon, true, 15));
    clearing->AddItem(items.back().get());
   
    items.push_back(make_unique<Item>("Old map", "You notice an \033[1;33mold map\033[0m, its marked with a red X.\n",ItemType::Map, true, 0));
    livingRoom->AddItem(items.back().get());

    items.push_back(make_unique<Item>("Flashlight", 
        "An old \033[1;33mflashlight\033[0m rests on the kitchen counter. Its battery compartment is empty.\n", ItemType::Flashlight, true));
    kitchen->AddItem(items.back().get());

    items.push_back(make_unique<Item>("Batteries",
        "Two dusty \033[1;33mbatteries\033[0m lie inside the rusted toolbox.\n", ItemType::Battery, true));
    basement->AddItem(items.back().get());

    //creation food
    items.push_back(make_unique<Item>("Berries",
        "A cluster of bright red \033[1;33mberries\033[0m grows beneath a twisted bush. They look fresh, although their unusual colour makes you hesitate.\n", 
        ItemType::Food, true, 10, 15));
    Item* berries = items.back().get();
    berries->SetQuantity(RandomBetween(2, 5));
    clearing->AddItem(berries);

    items.push_back(make_unique<Item>("Apple", "A surprisingly fresh red \033[1;33mapple\033[0m sits on the table.\n", ItemType::Food, true, 0, 15));
    kitchen->AddItem(items.back().get());

    //enemy
    //guardinan
    enemies.push_back(make_unique<Enemy>("Cave Guardian", "A towering \033[1;31mcreature\033[0m covered in black scales crouches in the darkness.\n"
                                         "Its pale eyes follow every movement you make.", 80, 18));
    Enemy* caveGuardian = enemies.back().get();
    tunnelRoom->AddEnemy(caveGuardian);
   
    //troll
    enemies.push_back(make_unique<Enemy>("Garden troll", "A massive \033[1;31mtroll\033[0m stands between you and the entrance of the house.\n", 40, 8, false));
    Enemy* gardenTroll = enemies.back().get();
    garden->AddEnemy(enemies.back().get());
    //item of troll
    items.push_back(make_unique<Item>("Basement Key", "A heavy iron key covered with dirt and rust.", ItemType::Key, true));
    gardenTroll->AddLoot(items.back().get());
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

    cout << "\n---------------------------------------------------------------------\n";
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

    cout << "You drop the \033[1;33m" << item->GetName() << "\033[0m.\n";

    if (item->GetItemType() == ItemType::Map)
    {
        hasMap = false;
    }
}

//--------------------------------------
//EAT a food
void Game::EatItem(const string& itemName)
{
    if (itemName.empty())
    {
        cout << "Eat what?\n";
        return;
    }

    Item* item = player->FindItem(itemName);

    if (item == nullptr)
    {
        cout << "You are not carrying " << itemName << ".\n";
        return;
    }

    if (item->GetItemType() != ItemType::Food)
    {
        cout << "You cannot eat the " << item->GetName() << ".\n";
        return;
    }

    if (player->GetHealth() == player->GetMaxHealth())
    {
        cout << "You are already at full health.\n";
        return;
    }

    const bool harmful = RandomBetween(1, 100) <= 45;

    if (!item->ConsumeOne())
    {
        cout << "There is nothing left to eat.\n";
        player->RemoveItem(item);
        return;
    }

    cout << "\nYou eat one of the "
        << item->GetName()
        << ".\n";

    if (harmful)
    {
        player->TakeDamage(item->GetDamage());

        cout << "\033[1;31mA sharp pain spreads through your stomach.\nYou lose " << item->GetDamage() << " HP.\033[0m\n";
    }
    else
    {
        player->Heal(item->GetHealingAmount());
        cout << "\033[1;32m" << "You recover " << item->GetHealingAmount() << " HP." << "\033[0m\n";
    }

    if (item->GetQuantity() == 0)
    {
        player->RemoveItem(item);
        cout << "There is none left.\n";
    }
    else
    {
        cout << "Remaining: " << item->GetQuantity() << "\n";
    }

    cout << "Health: " << player->GetHealth() << "/" << player->GetMaxHealth() << "\n";

    if (!player->IsAlive())
    {
        cout << "\n\033[1;31m" << "Your vision fades into darkness...\n" << "You have died." << "\033[0m\n";
        running = false;
    }
}

//--------------------------------------
//equip an item
void Game::EquipItem(const string& itemName)
{
    if (itemName.empty())
    {
        cout << "Equip what?\n";
        return;
    }

    Item* item = player->FindItem(itemName);

    if (item == nullptr)
    {
        cout << "You are not carrying "
            << itemName << ".\n";
        return;
    }

    if (!player->Equip(item))
    {
        cout << "You cannot equip that item.\n";
        return;
    }

    cout << "You equip the \033[1;33m" << item->GetName() << "\033[0m.\n"
        << "Your attack damage is now " << player->GetAttackDamage() << ".\n";
}

//--------------------------------------
void Game::AttackEnemy(const string& enemyName)
{
    if (enemyName.empty())
    {
        cout << "Attack what?\n";
        return;
    }

    Enemy* enemy = currentRoom->GetEnemy();

    if (enemy == nullptr)
    {
        cout << "There is no enemy called " << enemyName << " here.\n";
        return;
    }

    if (!enemy->IsAlive())
    {
        cout << "The " << enemy->GetName() << " is already dead.\n";
        return;
    }

    const bool enemyMissed = RandomBetween(1, 100) <= 15;
    cout << "\n---------------------------------------------------------------------\n";
   
    const int playerDamage = player->GetAttackDamage();
    enemy->TakeDamage(playerDamage);

    cout << "\nYou attack the \033[1;31m" << enemy->GetName() << "\033[0m and deal \033[1;33m" << playerDamage << " damage\033[0m\n"
         << enemy->GetName() << " health: " << enemy->GetHealth() << "/" << enemy->GetMaxHealth() << ".\n";
   

    if (!enemy->IsAlive())
    {
        cout << "\n\033[1;32mYou defeated the " << enemy->GetName() << "!\033[0m\n";
        cout << "\n\033[1;31mThe " << enemy->GetName() << " collapses to the ground.\033[0m\n";

        if (currentRoom == tunnelRoom)
        {
            cout << "The path to the \033[1;36mCrystal Cave\033[0m is now clear.\n";
            cout << "A cold blue light shines from the passage to the south.\n";
        }
        return;
    }
    if (enemyMissed)
    {
        cout << "\nThe " << enemy->GetName() << " attacks, but misses you.\n";
    }
    else
    {
        const int enemyDamage = RandomBetween(5, 15);
        player->TakeDamage(enemyDamage);

        cout << "\nThe \033[1;31m" << enemy->GetName() << "\033[0m attacks you and deals \033[1;31m" << enemyDamage << " damage\033[0m.\n"
            << "Your health: " << player->GetHealth() << "/" << player->GetMaxHealth() << ".\n";
    }

    if (!player->IsAlive())
    {
        cout << "\n\033[1;31mYour vision fades into darkness...\nYou have died.\033[0m\n";
        running = false;
    }
}

//--------------------------------------
void Game::LootEnemy()
{
    Enemy* enemy = currentRoom->GetEnemy();

    if (enemy == nullptr)
    {
        cout << "There is nothing to loot here.\n";
        return;
    }

    if (enemy->IsAlive())
    {
        cout << "You cannot loot the " << enemy->GetName() << " while it is still alive.\n";
        return;
    }

    if (!enemy->HasLoot())
    {
        cout << "You find nothing else on the " << enemy->GetName() << ".\n";
        return;
    }

    cout << "\nYou search the body of the " << enemy->GetName() << ".\n";

    while (enemy->HasLoot())
    {
        Item* item = enemy->TakeLoot();

        if (item != nullptr)
        {
            player->AddItem(item);
            cout << "You find: \033[1;33m" << item->GetName() << "\033[0m.\n";
        }
    }
}

//--------------------------------------
void Game::PutItem(const string& arguments)
{
    const size_t separator = arguments.find(" in ");

    if (separator == string::npos)
    {
        cout << "Use the sentence: put \033[1;33m<item>\033[0m in \033[1;33m<container>\033[0m\n";
        return;
    }

    const string itemName =
        arguments.substr(0, separator);

    const string containerName =
        arguments.substr(separator + 4);

    Item* item = player->FindItem(itemName);
    Item* container = player->FindItem(containerName);

    if (item == nullptr)
    {
        cout << "You are not carrying "
            << itemName << ".\n";
        return;
    }

    if (container == nullptr)
    {
        cout << "You are not carrying "
            << containerName << ".\n";
        return;
    }

    if (item == container)
    {
        cout << "You cannot put an item inside itself.\n";
        return;
    }

    if (!container->CanContainItems())
    {
        cout << container->GetName()
            << " cannot contain other items.\n";
        return;
    }

    if (container->GetItemType() == ItemType::Flashlight && item->GetItemType() != ItemType::Battery)
    {
        cout << "Only batteries fit inside the flashlight.\n";
        return;
    }

    cout << "You put the \033[1;33m" << itemName
        << "\033[0m inside the \033[1;33m" << containerName << "\033[0m.\n";       

    container->AddContent(item);
    player->RemoveItem(item);

    //only is is flashlight
    if (container->GetItemType() == ItemType::Flashlight)
    {
       cout << "The flashlight flickers, then produces a steady beam of light.\n";
    }
}

//--------------------------------------
//for the dark tunnel
bool Game::HasWorkingFlashlight() const
{
    Item* flashlight = player->FindItem("flashlight");

    if (flashlight == nullptr)
    {
        return false;
    }

    return flashlight->ContainsItemType(ItemType::Battery);
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
|         ^  ^  ^  ^  ^                                  |
|       ^               ^        .----------------.      |
|      ^   DARK FOREST   ^-------| FOREST CLEARING|      |
)MAP"

<< "|       ^               ^        |       \033[1;31mX\033[0m        |"  // had to do like this cause in the R"MAP i can't use colors

<< R"MAP(      |
|         ^  ^  ^  ^  ^          '-------+--------'      |
|                |                       :               |
|          .-----+------.                :               |
|          |  ABANDONED |                :               |
|          |   GARDEN   |                :               |
|          '-----+------'                :               |
|       _________|_____________          :               |
|      /                       \         :               |
|     /        OLD HOUSE        \        :               |
|    +--------+----------+-------+       :               |
|    | LIVING | ENTRANCE |KITCHEN|       :               |
|    |  ROOM  |          |       |       :               |
|    | (west) |          |(east) |       :               |
|    +----+---+----------+-------+       :               |
|         |                              :               |
|     +---+---------+                    :               |
|     |  BASEMENT   |                    :               |
|     +-------------+                    :               |
|                                   .----+----.          |
|                                  /   DARK    \         |
|                                 /   PASSAGE   \        |
|                                 '------+------'        |
|                                        |               |
|                                 * * * * * * * *        |
|                               *  CRYSTAL CAVE  *       |
|                                 * * * * * * * *        |
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
    bool itemInInventory = item != nullptr;

    if (item == nullptr)
    {
        item = currentRoom->FindItem(itemName);
    }

    Enemy* enemy = currentRoom->GetEnemy();

    if (item != nullptr)
    {
        if (itemInInventory)
        {
            cout << "\n\033[1;33m" << item->GetName() << "\033[0m\n";

            if (player->GetEquippedWeapon() == item)
            {
                cout << "You are holding the " << item->GetName() << " in your hand, ready to use it.\n";
            }
            else
            {
                cout << "You have the " << item->GetName() << " in your backpack.\n";
            }

            if (item->GetItemType() == ItemType::Flashlight)
            {
                if (item->ContainsItemType(ItemType::Battery))
                {
                    cout << "The flashlight contains \033[1;32mbatteries\033[0m and is ready to use.\n";
                }
                else
                {
                    cout << "The flashlight has no \033[1;32mbatteries\033[0m. You need to find some before it can work.\n";
                }
            }

            if (item->GetItemType() == ItemType::Map)
            {
                if (itemInInventory)
                {
                    ShowMap();
                }
                else
                {
                    cout << "You should pick up the map before unfolding it.\n";
                }
            }
        }
        else
        {
            item->Look();
        }

        return;

    }

    if (enemy != nullptr)
    {
        string enemyName = enemy->GetName();

        transform(enemyName.begin(), enemyName.end(), enemyName.begin(), [](unsigned char character)
            {
                return static_cast<char>(tolower(character));
            });

        if (enemyName.find(itemName) != string::npos)
        {
            if (enemy->IsAlive())
            {
                enemy->Look();
            }
            else
            {
                cout << "\nThe lifeless body of the \033[1;31m" << enemy->GetName() << "\033[0m lies on the ground.\n";
            }

            return;
        }
    }

    cout << "You cannot see anything called " << itemName << " here.\n";
}

//--------------------------------------
//Talk to the troll
void Game::TalkToEnemy(const string& enemyName)
{
    if (enemyName.empty())
    {
        cout << "Talk to whom?\n";
        return;
    }

    Enemy* enemy = currentRoom->GetEnemy();

    if (enemy == nullptr || enemy->GetName() != enemyName)
    {
        cout << "There is no " << enemyName << " here.\n";
        return;
    }

    if (!enemy->IsAlive())
    {
        cout << "The " << enemy->GetName() << " is dead and cannot answer.\n";
        return;
    }

    if (enemy->GetName() != "troll")
    {
        cout << "The " << enemy->GetName() << " does not seem interested in conversation.\n";
        return;
    }

    if (enemy->HasSpoken() && !enemy->IsHostile())
    {
        cout << "\"I have already given you the key,\" the troll mutters.\n";
        return;
    }
    const int enemyDamage = RandomBetween(20, 25);
   
    if (enemy->HasSpoken() && enemy->IsHostile())
    {
        cout << "\"You had your chance. Now, only blood will settle this!\"\n";
        cout << "The troll strikes you for \033[1;31m" << enemyDamage << " damage\033[0m.\n";

        player->TakeDamage(enemyDamage);

        if (!player->IsAlive())
        {
            cout << "\nYour vision fades into darkness...\n";
            cout << "\033[1;31mYou have died.\033[0m\n";
            running = false;
        }

        return;
    }

    cout << "\nThe troll raises one enormous hand.\n";
    cout << "\"Answer my question, and the key is yours.\"\n\n";
    cout << "\"What can answer you, although it never speaks first?\"\n";
    cout << "\nYour answer: ";

    string answer;
    getline(cin, answer);

    transform(answer.begin(), answer.end(), answer.begin(), [](unsigned char character)
        {
            return static_cast<char>(tolower(character));
        });

    enemy->SetHasSpoken(true);

    if (answer == "echo" || answer == "an echo")
    {
        enemy->SetHostile(false);

        cout << "\nThe troll smiles and slowly opens its hand.\n";
        cout << "\"Correct. A promise is a promise. Take the key.\"\n";

        Item* key = enemy->TakeLoot();

        if (key != nullptr)
        {
            player->AddItem(key);
            cout << "The troll gives you the \033[1;33m" << key->GetName() << "\033[0m.\n";
        }

        return;
    }

    enemy->SetHostile(true);

    
    player->TakeDamage(enemyDamage);

    cout << "\nThe troll's expression twists into rage.\n";
    cout << "\"Wrong answer!\"\n";
    cout << "The troll strikes you with tremendous force.\n";
    cout << "You lose \033[1;31m" << enemyDamage << " HP\033[0m.\n";

    player->TakeDamage(enemyDamage);

    if (!player->IsAlive())
    {
        cout << "\nYour vision fades into darkness...\n";
        cout << "\033[1;31mYou have died.\033[0m\n";
        running = false;
    }
}