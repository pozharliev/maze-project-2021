#include "../../include/frontend/room.h"

Room::~Room()
{
    delete mazeTile;
}

Room::Room(int mWidth, int mHeight)
{
    mazeWidth = mWidth;
    mazeHeight = mHeight;
    tileWidth = 13;
    tileHeight = 13;
    offsetX = 0.0f;
    offsetY = 0.0f;

    roomMaze = new CheckedMaze(mazeWidth, mazeHeight);

    generateRoom();
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

char Room::getTile(int x, int y)
{
    return roomMaze->checkedMaze[y * mazeWidth + x];
}

void Room::DrawRoom(olc::PixelGameEngine* engine)
{
    
    //Draw the Maze
    // for(int x = 0; x <= mazeWidth; x++)
    //     {
    //         for(int y = 0; y <= mazeHeight; y++)
    //         {
    //             char currentTile = getTile(x, y);
    //             switch(currentTile)
    //             {
    //                 case ' ':
    //                     break;
                    
    //                 case '#':
    //                     engine->FillRect(x * tileWidth, y * tileHeight, tileWidth, tileHeight, olc::Pixel(147,128,112));
    //                     break;
                    
    //                 default:
    //                     break;
    //             }
    //         }
    //     }

    for(int x = 0; x <= mazeWidth; x++)
        {
            for(int y = 0; y <= mazeHeight; y++)
            {
                char currentTile = getTile(x, y);
                switch(currentTile)
                {
                    case ' ':
                        // engine->FillRect(x * tileWidth, y * tileHeight, tileWidth, tileHeight, olc::BLANK);
                        engine->DrawSprite(x * tileWidth, y * tileHeight, mazeTile);
                        break;
                    
                    case '#':
                        break;
                    
                    default:
                        break;
                }
            }
        }
}