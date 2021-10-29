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

void Lobby::drawLobby(olc::PixelGameEngine *engine)
{

    auto getTile = [&](int x, int y)
    {
        if (x >= 0 && x < lobbyWidth && y >= 0 && y < lobbyWidth)
			return lobbyRawData[y * lobbyWidth + x];
    };

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


}