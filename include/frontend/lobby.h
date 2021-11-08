#pragma once

#include "../backend/libs.h"
#include "../frontend/player.h"
#include "../frontend/room.h"

class Lobby
{

private:
    int lobbyWidth;
    int lobbyHeight;
    std::string lobbyRawData;

    int tileWidth;
    int tileHeight;

    int visibleTilesX;
    int visibleTilesY;

    int mazePlayerPosX;
    int mazePlayerPosY;

public:
    Room *room;

    int thisLobbyCount;

    struct rect
    {
        olc::vf2d pos;
        olc::vf2d size;
    };

    rect stairCase;

    rect r;
    bool inMaze;
    olc::Sprite *lobbyRoom;
    olc::Sprite *lobbyForegroundSprite;
    olc::Decal *lobbyForeground;
    olc::Sprite *lobbyRoomUpper;
    olc::Sprite *lobbyForegroundUpperSprite;
    olc::Decal *lobbyForegroundUpper;
    olc::Sprite *lobbyRays;
    olc::Decal *lobbyRaysDecal;
    bool leftMazeEnter;
    bool rightMazeEnter;
    bool inLeftMaze;
    bool inRightMaze;
    enum MAZE_TYPE
    {
        LEFT,
        RIGHT
    };
    MAZE_TYPE currentMaze;

public:
    Lobby(int count);
    ~Lobby();
    /**
    * @brief Returns the symbol from the lobby array on x and y coordinates.
    **/
    char getTile(int x, int y);

    /**
    * @brief Displays the lobby.
    **/
    void drawLobby(olc::PixelGameEngine *engine, Player *player);

    /**
    * @brief Draws the foreground of the lobby(the objects infront of the player).
    **/
    void drawLobbyForeground(olc::PixelGameEngine *engine);

    /**
    * @brief Checks if the player is colliding with a rectangle(specifically for the doors).
    **/
    bool hallCollision(Player *player, rect roomLeft);

    /**
    * @brief Checks if the player is colliding with a rectangle.
    **/
    bool pointCollRect(const olc::vf2d &p, const rect &r);

private:

    /**
    * @brief Sets up important variables and data for the lobby.
    **/
    void initLobby();
};