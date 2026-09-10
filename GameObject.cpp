#include <iostream>

#include "GameObject.h"

GameObject::GameObject(const string& name, const string& description, ObjectType type) :
    name(name), description(description), type(type)
{
}

//--------------------------------------
void GameObject::Look() const
{
    cout << "\n" << name << "\n";
    cout << description << "\n";
}

const string& GameObject::GetName() const
{
    return name;
}

const string& GameObject::GetDescription() const
{
    return description;
}

ObjectType GameObject::GetType() const
{
    return type;
}