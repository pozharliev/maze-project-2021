#include "../../include/frontend/lobby.h"

Lobby::~Lobby()
{
    delete lobbyRoom;
}

void Lobby::initLobby()
{
    lobbyWidth = 32;
    lobbyHeight = 17;

    lobbyRawData += "................................";
    lobbyRawData += "................................";
	lobbyRawData += "....########################....";
	lobbyRawData += "....#......................#....";
	lobbyRawData += "....#......................#....";
	lobbyRawData += "....#......................#....";
	lobbyRawData += "#####......................#####";
	lobbyRawData += "................................";
	lobbyRawData += "................................";
	lobbyRawData += "................................";
	lobbyRawData += "................................";
	lobbyRawData += "#####......................#####";
	lobbyRawData += "....#......................#....";
	lobbyRawData += "....#......................#....";
	lobbyRawData += "....#......................#....";
	lobbyRawData += "....########################....";
	lobbyRawData += "................................";

    tileWidth = 11;
    tileHeight = 11;

    bool leftMazeEnter = false;
    bool rightMazeEnter = false;
}

//Draw the hall collision

bool Lobby::hallCollision(Player* player, rect roomLeft)
{
    return pointCollRect(player->playerPos, roomLeft);
}

bool Lobby::pointCollRect(const olc::vf2d &p, const rect &r)
{
    return (p.x >= r.pos.x && p.y >= r.pos.y && p.x < r.pos.x + r.size.x && p.y < r.pos.y + r.size.y);
}

char Lobby::getTile(int x, int y)
{
    if (x >= 0 && x < lobbyWidth && y >= 0 && y < lobbyWidth)
		return lobbyRawData[y * lobbyWidth + x];
}

void Lobby::drawLobby(olc::PixelGameEngine* engine, Player* player, Room* room)
{

    if(inMaze)
    {
        room->DrawRoom(engine);
        if(!leftMazeEnter)
        {
            player->playerX = abs(player->playerX - engine->ScreenWidth());
            leftMazeEnter = true;
        }
    }
    else
    {
        initLobby();
        visibleTilesX = engine->ScreenWidth() / tileWidth;
        visibleTilesY = engine->ScreenHeight() / tileHeight;

        // for(int x = 0; x < visibleTilesX; x++)
        // {
        //     for(int y = 0; y < visibleTilesY; y++)
        //     {
        //         char currentTile = getTile(x, y);
        //         switch(currentTile)
        //         {
        //             case '.':
        //                 engine->FillRect(x * tileWidth, y * tileHeight, (x + 1) * tileWidth, (y + 1) * tileHeight, olc::BLACK);
        //                 break;
                    
        //             case '#':
        //                 engine->FillRect(x * tileWidth, y * tileHeight, (x + 1) * tileWidth, (y + 1) * tileHeight, olc::RED);
        //                 break;
                    
        //             default:
        //                 break;
        //         }
        //     }
        // }

        rect roomLeft = {{-10.0f, engine->ScreenHeight() / 2.5f}, {10.0f, 43.0f}};
        engine->DrawRect(roomLeft.pos, roomLeft.size, olc::BLANK);

        rect roomRight = {{engine->ScreenWidth() - 1.0f, engine->ScreenHeight() / 2.5f}, {10.0f, 43.0f}};
        engine->DrawRect(roomRight.pos, roomRight.size, olc::BLANK);

        engine->DrawSprite(0, 0, lobbyRoom);

        if(hallCollision(player, roomLeft))
        {
            inMaze = true;
        }
    }
}