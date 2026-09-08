#pragma once

#include <map>
#include <string>

#include "GameObject.h"

class Room : public GameObject
{
public:
    Room(
        const std::string& name,
        const std::string& description
    );

    void Look() const override;

    void AddExit(const std::string& direction, Room* destination, const std::string& viewDescription);

    Room* GetExit(const std::string& direction) const;

private:
    struct ExitInfo
    {
        Room* destination;
        std::string viewDescription;
    };

    std::map<std::string, ExitInfo> exits;
};