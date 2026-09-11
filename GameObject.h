#pragma once //I use this instead of #ifndef #define #endif 

#include <string>
#include <list>

using namespace std;

//--------------------------------------
//all things of the game have this base
enum class ObjectType
{
    Room,
    Item,
    Food,
    Container,
    Player,
    Enemy
};

//--------------------------------------
class GameObject
{
public:
    GameObject(const string& name, const string& description, ObjectType type);

    virtual ~GameObject() = default;
    virtual void Look() const;
    const string& GetName() const;
    const string& GetDescription() const;
    ObjectType GetType() const;

protected:

    string name;
    string description;
    ObjectType type;
};