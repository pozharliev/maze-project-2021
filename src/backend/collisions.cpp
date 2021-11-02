#include "../../include/backend/collisions.h"

void Collisions::checkCollisions(Player* player, Lobby* lobby, Room* room)
{
    if(!lobby->inMaze)
    {
        if(player->playerDir == player->PLAYER_DIRS::LEFT)
        {
            if(lobby->getTile((int)(player->newPlayerPosX / 11), (int)(player->newPlayerPosY / 11)) != '.' || lobby->getTile((int)(player->newPlayerPosX / 11), (int)(player->newPlayerPosY / 11) + 0.9f) != '.')
            {
                player->playerX = (int)player->newPlayerPosX + 1;
                player->playerVelX = 0;
            }
        }

        if(player->playerDir == player->PLAYER_DIRS::RIGHT)
        {
            if(lobby->getTile((int)(player->newPlayerPosX / 11) + 1.0f, (int)(player->newPlayerPosY / 11)) != '.' || lobby->getTile((int)(player->newPlayerPosX / 11) + 1.0f, (int)(player->newPlayerPosY / 11) + 0.9f) != '.')
            {
                player->playerX = (int)player->newPlayerPosX;
                player->playerVelX = 0;
            }
        }

        if(player->playerDir == player->PLAYER_DIRS::UP)
        {
            if(lobby->getTile((int)(player->newPlayerPosX / 11), (int)(player->newPlayerPosY / 11)) != '.' || lobby->getTile((int)(player->newPlayerPosX / 11) + 0.9f, (int)(player->newPlayerPosY / 11)) != '.')
            {
                player->playerY = (int)player->newPlayerPosY + 1;
                player->playerVelY = 0;
            }
        }

        if(player->playerDir == player->PLAYER_DIRS::DOWN && !player->firstPlayerMove)
        {
            if(lobby->getTile((int)(player->newPlayerPosX / 11) + 0.0f, (int)(player->newPlayerPosY / 11) + 1.0f) != '.' || lobby->getTile((int)(player->newPlayerPosX / 11) + 0.9f, (int)(player->newPlayerPosY / 11) + 1.0f) != '.')
            {
                player->playerY = (int)player->newPlayerPosY;
                player->playerVelY = 0;
            }
        }
    }

};