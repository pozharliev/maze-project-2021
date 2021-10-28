#include "../../include/frontend/room.h"

Room::Room(int mWidth, int mHeight)
{
    mazeWidth = mWidth;
    mazeHeight = mHeight;
    tileWidth = 16;
    tileHeight = 16;

    roomMaze = new CheckedMaze(mazeWidth, mazeHeight);
}

void Room::generateRoom()
{
    rawMazeData.open("data/rawMazeData.maze", std::ofstream::out);

    for (int i = 0; i <= roomMaze->getHeight(); i++)
    {
        for (int j = 0; j <= roomMaze->getWidth(); j++)
        {
            if (roomMaze->checkedMaze[i * roomMaze->getWidth() + j] == '#')
            {
                rawMazeData << "1";
            }
            else if (roomMaze->checkedMaze[i * roomMaze->getWidth() + j] == ' ')
            {
                rawMazeData << "0";
            }
        }
        rawMazeData << '\n';
    }

    rawMazeData.close();
}

void Room::DrawRoom(olc::PixelGameEngine* engine)
{

    //Number of tiles visible for the player
    visibleTilesX = engine->ScreenWidth() / tileWidth;
    visibleTilesY = engine->ScreenHeight() / tileHeight;

    offsetX = CameraPosX - (float)visibleTilesX / 2.0f;
    offsetY = CameraPosY - (float)visibleTilesY / 2.0f;

    //Offset the maze based on the player position
    if(offsetX < 0) offsetX = 0;
    if(offsetY < 0) offsetY = 0;

    if (offsetX > roomMaze->getWidth() - visibleTilesX) offsetX = roomMaze->getWidth() - visibleTilesX;
	if (offsetY > roomMaze->getHeight() - visibleTilesY) offsetY = roomMaze->getHeight() - visibleTilesY;


    //Draw the Maze

    rawMazeData.open("data/rawMazeData.maze");

    for(int x = 0; x < visibleTilesX; x++)
    {
        for(int y = 0; y < visibleTilesY; y++)
        {
            char currentTile = roomMaze->checkedMaze[y * roomMaze->getWidth() + x];

            switch(currentTile)
            {
                case ' ':
                    engine->FillRect(x * tileWidth, y * tileHeight, (x + 1) * tileWidth, (y + 1) * tileHeight, olc::RED);
                    break;

                case '#':
                    engine->FillRect(x * tileWidth, y * tileHeight, (x + 1) * tileWidth, (y + 1) * tileHeight, olc::BLACK);
                    break;
            }
            
        }
    }
    
    
}

//# - 1
//" " - 0