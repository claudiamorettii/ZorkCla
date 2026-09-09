#pragma once

#include <map>
#include <string>

#include "GameObject.h"

class Room : public GameObject
{
public:
    Room(const string& name, const string& description);

    void Look() const override;

    void AddExit(const string& direction, Room* destination, const string& viewDescription);

    Room* GetExit(const string& direction) const;

private:
    struct ExitInfo
    {
        Room* destination;
        string viewDescription;
    };

    map <string, ExitInfo> exits;
};