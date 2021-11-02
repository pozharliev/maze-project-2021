#include "../../include/backend/collisions.h"

void Collisions::checkCollisions(Player* player, Lobby* lobby, Room* room)
{
    // if(lobby->inMaze)
    // {
    //   if(player->playerVelX <= 0)
    //   {
    //     if(room->getTile(player->newPlayerPosX + 0.0f, player->playerY + 0.0f) != ' ' || room->getTile(player->newPlayerPosX + 0.0f, player->playerY + 0.9f) != ' ')
    //     {
    //         player->newPlayerPosX = (int)player->newPlayerPosX + 1;
    //         player->playerVelX = 0;
    //     }
    //   }
    //   else
    //   {
    //     if(room->getTile(player->newPlayerPosX + 1.0f, player->playerY + 0.0f) != ' ' || room->getTile(player->newPlayerPosX + 1.0f, player->playerY + 0.9f) != ' ')
    //     {
    //         player->newPlayerPosX =(int) player->newPlayerPosX;
    //         player->playerVelX = 0;
    //     }
        
    //     if(!lobby->firstMazeEnter)
    //     {
    //         player->playerX = player->newPlayerPosX;
    //         player->playerY = player->newPlayerPosY;
    //     }
    //   }
    // }
    // else
    // {
    //   if(player->playerVelX <= 0)
    //   {
    //     if(lobby->getTile(player->newPlayerPosX + 0.0f, player->playerY + 0.0f) != ' ' || lobby->getTile(player->newPlayerPosX + 0.0f, player->playerY + 0.9f) != ' ')
    //     {
    //         player->newPlayerPosX = (int)player->newPlayerPosX + 1;
    //         player->playerVelX = 0;
    //     }
    //   }
    //   else
    //   {
    //     if(lobby->getTile(player->newPlayerPosX + 1.0f, player->playerY + 0.0f) != ' ' || lobby->getTile(player->newPlayerPosX + 1.0f, player->playerY + 0.9f) != ' ')
    //     {
    //         player->newPlayerPosX =(int) player->newPlayerPosX;
    //         player->playerVelX = 0;
    //     }
        
    //     if(!lobby->firstMazeEnter)
    //     {
    //         player->playerX = player->newPlayerPosX;
    //         player->playerY = player->newPlayerPosY;
    //     }
    //   }
    // }

    //std::cout<<lobby->getTile((int)player->playerX * 11, (int)player->playerY * 11);
    std::cout<<lobby->getTile((int)(player->newPlayerPosX / 11), (int)(player->newPlayerPosY / 11))<<std::endl;

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

        if(player->playerDir == player->PLAYER_DIRS::DOWN)
        {
            if(lobby->getTile((int)(player->newPlayerPosX / 11) + 0.0f, (int)(player->newPlayerPosY / 11) + 1.0f) != '.' || lobby->getTile((int)(player->newPlayerPosX / 11) + 0.9f, (int)(player->newPlayerPosY / 11) + 1.0f) != '.')
            {
                player->playerY = (int)player->newPlayerPosY;
                player->playerVelY = 0;
                std::cout<<"COLLIDING";
            }
        }
    }

    
};