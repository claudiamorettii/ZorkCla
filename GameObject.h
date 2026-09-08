#pragma once

#include <string>

enum class ObjectType
{
    Room,
    Item,
    Food,
    Container,
    Player
};

class GameObject
{
public:
    GameObject(const std::string& name, const std::string& description, ObjectType type);

    virtual ~GameObject() = default;

    virtual void Look() const;

    const std::string& GetName() const;
    const std::string& GetDescription() const;
    ObjectType GetType() const;

protected:
    std::string name;
    std::string description;
    ObjectType type;
};