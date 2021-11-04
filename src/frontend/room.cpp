#include "../../include/frontend/room.h"

Room::~Room()
{
    delete mazeTile;
    delete runeSprite;
    delete rune;
}

Room::Room(int mWidth, int mHeight)
{
    mazeWidth = mWidth;
    mazeHeight = mHeight;
    tileWidth = 13;
    tileHeight = 13;

    leftMaze = new CheckedMaze(mazeWidth, mazeHeight);
    rightMaze = new CheckedMaze(mazeWidth, mazeHeight);

    mazeTile = new olc::Sprite("public/tile.png");

    generateRoom();
}

void Room::generateRoom()
{
    rawMazeData.open("data/leftRawMazeData.maze", std::ofstream::out);

    for (int i = 0; i <= mazeHeight; i++)
    {
        for (int j = 0; j <= mazeWidth; j++)
        {
            if (leftMaze->reversedMaze[i * mazeWidth + j] == '#')
            {
                rawMazeData << "1";
            }
            else if (leftMaze->reversedMaze[i * mazeWidth + j] == ' ')
            {
                rawMazeData << "0";
            }
        }
        rawMazeData << '\n';
    }

    rawMazeData.close();

    rawMazeData.open("data/rightRawMazeData.maze", std::ofstream::out);

    for (int i = 0; i <= mazeHeight; i++)
    {
        for (int j = 0; j <= mazeWidth; j++)
        {
            if (rightMaze->checkedMaze[i * mazeWidth + j] == '#')
            {
                rawMazeData << "1";
            }
            else if (rightMaze->checkedMaze[i * mazeWidth + j] == ' ')
            {
                rawMazeData << "0";
            }
        }
        rawMazeData << '\n';
    }

    rawMazeData.close();
}

char Room::getTile(std::string mazeOrientation, int x, int y)
{
    return (mazeOrientation == "left") ? leftMaze->reversedMaze[y * mazeWidth + x] : rightMaze->checkedMaze[y * mazeWidth + x];
}

void Room::DrawRoom(olc::PixelGameEngine *engine, std::string mazeOrientation)
{

    leftMaze->printReversedMaze();

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
    if (mazeOrientation == "left")
    {
        for (int x = 0; x <= mazeWidth; x++)
        {
            for (int y = 0; y <= mazeHeight; y++)
            {
                char currentTile = getTile("left", x, y);
                switch (currentTile)
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

                if (x == mazeWidth - 1 && y == mazeHeight - 1)
                {
                    engine->DrawDecal({x * tileWidth, y * tileHeight}, runeTile);
                }

                if (x == mazeWidth - 1 && y == mazeHeight - 1)
                {
                    engine->DrawDecal({x * tileWidth + 1.5f, y * tileHeight}, rune, {0.55f, 0.55f});
                }
            }
        }
    }
    else
    {
        for (int x = 0; x <= mazeWidth; x++)
        {
            for (int y = 0; y <= mazeHeight; y++)
            {
                char currentTile = getTile("right", x, y);
                switch (currentTile)
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

                if (x == mazeWidth - 1 && y == mazeHeight - 1)
                {
                    engine->DrawDecal({x * tileWidth, y * tileHeight}, runeTile);
                }

                if (x == mazeWidth - 1 && y == mazeHeight - 1)
                {
                    engine->DrawDecal({x * tileWidth + 1.5f, y * tileHeight}, rune, {0.55f, 0.55f});
                }
            }
        }
    }
}