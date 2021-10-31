#pragma once

#include "libs.h"
#include "../frontend/player.h"
#include "../frontend/lobby.h"

class Collisions
{
    public:
        void checkCollisions(Player* player, Lobby* lobby, Room* room);
};