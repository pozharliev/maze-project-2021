#include "../../include/backend/collisions.h"

void Collisions::checkCollisions(olc::PixelGameEngine* engine, Player* player, Lobby* lobby, Room* room)
{
    if(!lobby->inMaze)
    {
        if(player->playerDir == player->PLAYER_DIRS::LEFT)
        {
            if(lobby->getTile((int)(player->newPlayerPosX / 11), (int)(player->newPlayerPosY / 11)) != '.' || lobby->getTile((int)(player->newPlayerPosX / 11), (int)(player->newPlayerPosY / 11) + 0.9f) != '.')
            {
                player->playerX = (int)player->newPlayerPosX + 1;
                player->playerVelX = 0;
                colliding = true;
                lastCollisionDir = player->PLAYER_DIRS::LEFT;
            } else { lastCollisionDir = player->PLAYER_DIRS::NONE; }
        }

        if(player->playerDir == player->PLAYER_DIRS::RIGHT)
        {
            if(lobby->getTile((int)(player->newPlayerPosX / 11) + 1.0f, (int)(player->newPlayerPosY / 11)) != '.' || lobby->getTile((int)(player->newPlayerPosX / 11) + 1.0f, (int)(player->newPlayerPosY / 11) + 0.9f) != '.')
            {
                player->playerX = (int)player->newPlayerPosX;
                player->playerVelX = 0;
                colliding = true;
                lastCollisionDir = player->PLAYER_DIRS::RIGHT;
            } else { lastCollisionDir = player->PLAYER_DIRS::NONE; }
        }

        if(player->playerDir == player->PLAYER_DIRS::UP)
        {
            if(lobby->getTile((int)(player->newPlayerPosX / 11), (int)(player->newPlayerPosY / 11)) != '.' || lobby->getTile((int)(player->newPlayerPosX / 11) + 0.9f, (int)(player->newPlayerPosY / 11)) != '.')
            {
                player->playerY = (int)player->newPlayerPosY + 1;
                player->playerVelY = 0;
                colliding = true;
                lastCollisionDir = player->PLAYER_DIRS::UP;
            } else { lastCollisionDir = player->PLAYER_DIRS::NONE; }
        }

        if(player->playerDir == player->PLAYER_DIRS::DOWN && !player->firstPlayerMove)
        {
            if(lobby->getTile((int)(player->newPlayerPosX / 11) + 0.0f, (int)(player->newPlayerPosY / 11) + 1.0f) != '.' || lobby->getTile((int)(player->newPlayerPosX / 11) + 0.9f, (int)(player->newPlayerPosY / 11) + 1.0f) != '.')
            {
                player->playerY = (int)player->newPlayerPosY;
                player->playerVelY = 0;
                colliding = true;
                lastCollisionDir = player->PLAYER_DIRS::DOWN;
            } else { lastCollisionDir = player->PLAYER_DIRS::NONE; }
        }
    }

    if(lobby->inMaze)
    {
        mazeOrientation = (lobby->currentMaze == Lobby::MAZE_TYPE::LEFT) ? "left" : "right";

        Lobby::rect roomLeftBack = {{engine->ScreenWidth() -1.0f, engine->ScreenHeight() / 2.5f}, {10.0f, 43.0f}};
        Lobby::rect roomRightBack = {{0.0f, engine->ScreenHeight() / 2.5f}, {10.0f, 43.0f}};
        if(lobby->inLeftMaze)
        {
            if(lobby->hallCollision(player, roomLeftBack))
            {
                player->playerX = 15.0f;
                lobby->inMaze = false;
                lobby->inLeftMaze = false;
            }
        }
        else
        {
            if(lobby->hallCollision(player, roomRightBack))
            {
                lobby->inMaze = false;
                lobby->inRightMaze = false;
                player->playerX = engine->ScreenWidth() - 15.0f;
            }
        }

        if(player->playerDir == player->PLAYER_DIRS::LEFT)
        {
            if(room->getTile(mazeOrientation, (int)(player->newPlayerPosX / 13), (int)(player->newPlayerPosY / 13)) != ' ' || room->getTile(mazeOrientation, (int)(player->newPlayerPosX / 13), (int)(player->newPlayerPosY / 13) + 0.4f) != ' ')
            {
                //End game
            } else { lastCollisionDir = player->PLAYER_DIRS::NONE; }
        }

        if(player->playerDir == player->PLAYER_DIRS::RIGHT)
        {
            if(room->getTile(mazeOrientation, (int)(player->newPlayerPosX / 13) + 0.6f, (int)(player->newPlayerPosY / 13)) != ' ' || room->getTile(mazeOrientation, (int)(player->newPlayerPosX / 13) + 0.6f, (int)(player->newPlayerPosY / 13) + 0.4f) != ' ')
            {
                //End game
            } else { lastCollisionDir = player->PLAYER_DIRS::NONE; }
        }

        if(player->playerDir == player->PLAYER_DIRS::UP)
        {
            if(room->getTile(mazeOrientation, (int)(player->newPlayerPosX / 13), (int)(player->newPlayerPosY / 13)) != ' ' || room->getTile(mazeOrientation, (int)(player->newPlayerPosX / 13) + 0.4f, (int)(player->newPlayerPosY / 13)) != ' ')
            {
                //End game
            } else { lastCollisionDir = player->PLAYER_DIRS::NONE; }
        }

        if(player->playerDir == player->PLAYER_DIRS::DOWN && !player->firstPlayerMove)
        {
            if(room->getTile(mazeOrientation, (int)(player->newPlayerPosX / 13) + 0.0f, (int)(player->newPlayerPosY / 13) + 0.5f) != ' ' || room->getTile(mazeOrientation, (int)(player->newPlayerPosX / 13) + 0.4f, (int)(player->newPlayerPosY / 13) + 0.6f) != ' ')
            {
                //End game
            } else { lastCollisionDir = player->PLAYER_DIRS::NONE; }
        }
        

        


    }

};