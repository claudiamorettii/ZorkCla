#include <iostream>

#include "GameObject.h"

GameObject::GameObject(
    const std::string& name,
    const std::string& description,
    ObjectType type
)
    : name(name),
    description(description),
    type(type)
{
}

void GameObject::Look() const
{
    std::cout << "\n" << name << "\n";
    std::cout << description << "\n";
}

const std::string& GameObject::GetName() const
{
    return name;
}

const std::string& GameObject::GetDescription() const
{
    return description;
}

ObjectType GameObject::GetType() const
{
    return type;
}