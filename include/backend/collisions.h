#pragma once

#include "libs.h"
#include "../frontend/player.h"
#include "../frontend/lobby.h"

class Collisions
{
public:
    bool colliding;
    Player::PLAYER_DIRS lastCollisionDir;
    std::string mazeOrientation;
    bool gameEnded;

public:
    /**
    * @brief Checks for collisions with the player in the lobby and the rooms.
    * @brief Detects and manages when the player picks up a scroll.
    **/
    void checkCollisions(olc::PixelGameEngine *engine, Player *player, Lobby *lobby, Room *room);
};