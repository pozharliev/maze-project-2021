#include "../../include/frontend/lobby.h"

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

void Lobby::drawLobby(olc::PixelGameEngine* engine, Player* player, Room* room)
{
    auto getTile = [&](int x, int y)
    {
        if (x >= 0 && x < lobbyWidth && y >= 0 && y < lobbyWidth)
			return lobbyRawData[y * lobbyWidth + x];
    };

    if(inMaze)
    {
        room->generateRoom();
        room->DrawRoom(engine, player);
    }
    else
    {
        initLobby();
        visibleTilesX = engine->ScreenWidth() / tileWidth;
        visibleTilesY = engine->ScreenHeight() / tileHeight;

        for(int x = 0; x < visibleTilesX; x++)
        {
            for(int y = 0; y < visibleTilesY; y++)
            {
                char currentTile = getTile(x, y);
                switch(currentTile)
                {
                    case '.':
                        engine->FillRect(x * tileWidth, y * tileHeight, (x + 1) * tileWidth, (y + 1) * tileHeight, olc::BLACK);
                        break;
                    
                    case '#':
                        engine->FillRect(x * tileWidth, y * tileHeight, (x + 1) * tileWidth, (y + 1) * tileHeight, olc::RED);
                        break;
                    
                    default:
                        break;
                }
            }
        }

        rect roomLeft = {{0, engine->ScreenHeight() / 2.5f}, {10.0f, 43.0f}};
        engine->DrawRect(roomLeft.pos, roomLeft.size, olc::RED);

        if(hallCollision(player, roomLeft))
        {
            inMaze = true;
        }
    }
}