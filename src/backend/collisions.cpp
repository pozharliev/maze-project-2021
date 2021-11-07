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
                if(room->getTile(mazeOrientation, (int)(player->newPlayerPosX / 13), (int)(player->newPlayerPosY / 13)) == 'R' || room->getTile(mazeOrientation, (int)(player->newPlayerPosX / 13), (int)(player->newPlayerPosY / 13) + 0.4f) == 'R')
                {
                    if(mazeOrientation == "left" && lobby->room->leftRunePickedUp == false)
                    {
                        PlaySoundA("public/sfx/runePickUp.wav", NULL, SND_ASYNC);
                        lobby->room->leftRunePickedUp = true;
                        player->playerInv.runes++;
                    }
                    else if(mazeOrientation == "right" && lobby->room->rightRunePickedUp == false)
                    {
                        PlaySoundA("public/sfx/runePickUp.wav", NULL, SND_ASYNC);
                        lobby->room->rightRunePickedUp = true;
                        player->playerInv.runes++;
                    }
                }

                if(room->getTile(mazeOrientation, (int)(player->newPlayerPosX / 13), (int)(player->newPlayerPosY / 13)) != '#' || room->getTile(mazeOrientation, (int)(player->newPlayerPosX / 13), (int)(player->newPlayerPosY / 13) + 0.4f) != '#')
                {
                    for(auto i : room->items_vec)
                    {
                        if(i.x == (int)(player->newPlayerPosX / 13) || i.y == (int)(player->newPlayerPosY / 13))
                        {
                            if(i.pickedUp == false)
                            {
                                PlaySoundA("public/sfx/scrollPickUp.wav", NULL, SND_ASYNC);
                                if(i.type == "path")
                                {
                                    player->playerInv.pathScroll = true;
                                }
                                if(i.type == "dash")
                                {
                                    player->playerInv.dashScroll = true;
                                }
                                if(i.type == "speed")
                                {
                                    player->playerSpeed = 70.0f;
                                    player->playerInv.speedScroll = true;
                                }
                                
                            }
                            i.pickedUp = true;
                        }
                    }
                 } //else { gameEnded = true; }
                
            } else { lastCollisionDir = player->PLAYER_DIRS::NONE; }
        }

        if(player->playerDir == player->PLAYER_DIRS::RIGHT)
        {
            if(room->getTile(mazeOrientation, (int)(player->newPlayerPosX / 13) + 0.6f, (int)(player->newPlayerPosY / 13)) != ' ' || room->getTile(mazeOrientation, (int)(player->newPlayerPosX / 13) + 0.6f, (int)(player->newPlayerPosY / 13) + 0.4f) != ' ')
            {

                if(room->getTile(mazeOrientation, (int)(player->newPlayerPosX / 13) + 0.6f, (int)(player->newPlayerPosY / 13)) == 'R' || room->getTile(mazeOrientation, (int)(player->newPlayerPosX / 13) + 0.6f, (int)(player->newPlayerPosY / 13) + 0.4f) == 'R')
                {
                    if(mazeOrientation == "left" && lobby->room->leftRunePickedUp == false)
                    {
                        PlaySoundA("public/sfx/runePickUp.wav", NULL, SND_ASYNC);
                        lobby->room->leftRunePickedUp = true;
                        player->playerInv.runes++;
                    }
                    else if(mazeOrientation == "right" && lobby->room->rightRunePickedUp == false)
                    {
                        PlaySoundA("public/sfx/runePickUp.wav", NULL, SND_ASYNC);
                        lobby->room->rightRunePickedUp = true;
                        player->playerInv.runes++;
                    }
                }

                if(room->getTile(mazeOrientation, (int)(player->newPlayerPosX / 13), (int)(player->newPlayerPosY / 13)) != '#' || room->getTile(mazeOrientation, (int)(player->newPlayerPosX / 13), (int)(player->newPlayerPosY / 13) + 0.4f) != '#')
                {
                    for(auto i : room->items_vec)
                    {
                        if(i.x == (int)(player->newPlayerPosX / 13) || i.y == (int)(player->newPlayerPosY / 13))
                        {
                            if(i.pickedUp == false)
                            {
                                PlaySoundA("public/sfx/scrollPickUp.wav", NULL, SND_ASYNC);
                                if(i.type == "path")
                                {
                                    player->playerInv.pathScroll = true;
                                }
                                if(i.type == "dash")
                                {
                                    player->playerInv.dashScroll = true;
                                }
                                if(i.type == "speed")
                                {
                                    player->playerSpeed = 70.0f;
                                    player->playerInv.speedScroll = true;
                                }
                               
                            }
                            i.pickedUp = true;
                        }
                    }
                } //else { gameEnded = true; }

            } else { lastCollisionDir = player->PLAYER_DIRS::NONE; }
        }

        if(player->playerDir == player->PLAYER_DIRS::UP)
        {
            if(room->getTile(mazeOrientation, (int)(player->newPlayerPosX / 13), (int)(player->newPlayerPosY / 13)) != ' ' || room->getTile(mazeOrientation, (int)(player->newPlayerPosX / 13) + 0.4f, (int)(player->newPlayerPosY / 13)) != ' ')
            {

                if(room->getTile(mazeOrientation, (int)(player->newPlayerPosX / 13), (int)(player->newPlayerPosY / 13)) == 'R' || room->getTile(mazeOrientation, (int)(player->newPlayerPosX / 13) + 0.4f, (int)(player->newPlayerPosY / 13)) == 'R')
                {
                    if(mazeOrientation == "left" && lobby->room->leftRunePickedUp == false)
                    {
                        PlaySoundA("public/sfx/runePickUp.wav", NULL, SND_ASYNC);
                        lobby->room->leftRunePickedUp = true;
                        player->playerInv.runes++;
                    }
                    else if(mazeOrientation == "right" && lobby->room->rightRunePickedUp == false)
                    {
                        PlaySoundA("public/sfx/runePickUp.wav", NULL, SND_ASYNC);
                        lobby->room->rightRunePickedUp = true;
                        player->playerInv.runes++;
                    }
                }

                if(room->getTile(mazeOrientation, (int)(player->newPlayerPosX / 13), (int)(player->newPlayerPosY / 13)) != '#' || room->getTile(mazeOrientation, (int)(player->newPlayerPosX / 13), (int)(player->newPlayerPosY / 13) + 0.4f) != '#')
                {
                    for(auto i : room->items_vec)
                    {
                        if(i.x == (int)(player->newPlayerPosX / 13) || i.y == (int)(player->newPlayerPosY / 13))
                        {
                            if(i.pickedUp == false)
                            {
                                PlaySoundA("public/sfx/scrollPickUp.wav", NULL, SND_ASYNC);
                                if(i.type == "path")
                                {
                                    player->playerInv.pathScroll = true;
                                }
                                if(i.type == "dash")
                                {
                                    player->playerInv.dashScroll = true;
                                }
                                if(i.type == "speed")
                                {
                                    player->playerSpeed = 70.0f;
                                    player->playerInv.speedScroll = true;
                                }
                            }
                            i.pickedUp = true;
                        }
                    }
                 } //else { gameEnded = true; }
            } else { lastCollisionDir = player->PLAYER_DIRS::NONE; }
        }

        if(player->playerDir == player->PLAYER_DIRS::DOWN && !player->firstPlayerMove)
        {
            if(room->getTile(mazeOrientation, (int)(player->newPlayerPosX / 13) + 0.0f, (int)(player->newPlayerPosY / 13) + 0.5f) != ' ' || room->getTile(mazeOrientation, (int)(player->newPlayerPosX / 13) + 0.4f, (int)(player->newPlayerPosY / 13) + 0.6f) != ' ')
            {

                if(room->getTile(mazeOrientation, (int)(player->newPlayerPosX / 13) + 0.0f, (int)(player->newPlayerPosY / 13) + 0.5f) == 'R' || room->getTile(mazeOrientation, (int)(player->newPlayerPosX / 13) + 0.4f, (int)(player->newPlayerPosY / 13) + 0.6f) == 'R')
                {
                    if(mazeOrientation == "left" && lobby->room->leftRunePickedUp == false)
                    {
                        PlaySoundA("public/sfx/runePickUp.wav", NULL, SND_ASYNC);
                        lobby->room->leftRunePickedUp = true;
                        player->playerInv.runes++;
                    }
                    else if(mazeOrientation == "right" && lobby->room->rightRunePickedUp == false)
                    {
                        PlaySoundA("public/sfx/runePickUp.wav", NULL, SND_ASYNC);
                        lobby->room->rightRunePickedUp = true;
                        player->playerInv.runes++;
                    }
                }

                if(room->getTile(mazeOrientation, (int)(player->newPlayerPosX / 13), (int)(player->newPlayerPosY / 13)) != '#' || room->getTile(mazeOrientation, (int)(player->newPlayerPosX / 13), (int)(player->newPlayerPosY / 13) + 0.4f) != '#')
                {
                    for(auto i : room->items_vec)
                    {
                        if(i.x == (int)(player->newPlayerPosX / 13) || i.y == (int)(player->newPlayerPosY / 13))
                        {
                            if(i.pickedUp == false)
                            {
                                PlaySoundA("public/sfx/scrollPickUp.wav", NULL, SND_ASYNC);
                                if(i.type == "path")
                                {
                                    player->playerInv.pathScroll = true;
                                }
                                if(i.type == "dash")
                                {
                                    player->playerInv.dashScroll = true;
                                }
                                if(i.type == "speed")
                                {
                                    player->playerInv.speedScroll = true;
                                    player->playerSpeed = 70.0f;
                                }
                                
                            }
                            i.pickedUp = true;
                        }
                    }
                 } //else { gameEnded = true; }
            } else { lastCollisionDir = player->PLAYER_DIRS::NONE; }
        }
    
    }

};