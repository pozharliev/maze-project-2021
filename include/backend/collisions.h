#pragma once

#include "libs.h"
#include "../frontend/player.h"
#include "../frontend/lobby.h"

class Collisions
{
    public:
        bool colliding;
        Player::PLAYER_DIRS lastCollisionDir;
        
    public:
        void checkCollisions(olc::PixelGameEngine* engine, Player* player, Lobby* lobby, Room* room);
};