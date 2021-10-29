#include "../../include/frontend/room.h"

Room::Room(int mWidth, int mHeight)
{
    mazeWidth = mWidth;
    mazeHeight = mHeight;
    tileWidth = 16;
    tileHeight = 16;
    offsetX = 0.0f;
    offsetY = 0.0f;

    roomMaze = new CheckedMaze(mazeWidth, mazeHeight);
}

void Room::generateRoom()
{
    rawMazeData.open("data/rawMazeData.maze", std::ofstream::out);

    for (int i = 0; i <= mazeHeight; i++)
    {
        for (int j = 0; j <= mazeWidth; j++)
        {
            if (roomMaze->checkedMaze[i * mazeWidth + j] == '#')
            {
                rawMazeData << "1";
            }
            else if (roomMaze->checkedMaze[i * mazeWidth + j] == ' ')
            {
                rawMazeData << "0";
            }
        }
        rawMazeData << '\n';
    }

    rawMazeData.close();
}

void Room::DrawRoom(olc::PixelGameEngine* engine, Player* player)
{
    auto getTile = [&](int x, int y)
    {
        if (x >= 0 && x < mazeWidth && y >= 0 && y < mazeHeight)
				return roomMaze->checkedMaze[y * mazeWidth + x];
    };

    cameraPosX = player->playerX;
    cameraPosY = player->playerY;

    //Number of tiles visible for the player
    visibleTilesX = engine->ScreenWidth() / tileWidth;
    visibleTilesY = engine->ScreenHeight() / tileHeight;

    offsetX = cameraPosX - (float)visibleTilesX / 2.0f;
    offsetY = cameraPosY - (float)visibleTilesY / 2.0f;


    //Offset the maze based on the player position
    if(offsetX < 0) offsetX = 0;
    if(offsetY < 0) offsetY = 0;

    if (offsetX > mazeWidth - visibleTilesX) offsetX = mazeWidth - visibleTilesX;
	if (offsetY > mazeHeight - visibleTilesY) offsetY = mazeHeight - visibleTilesY;


    //Draw the Maze
    for(int x = 0; x < visibleTilesX; x++)
    {
        for(int y = 0; y < visibleTilesY; y++)
        {
            char currentTile = getTile(x + offsetX, y + offsetY);

            switch(currentTile)
            {
                case ' ':
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