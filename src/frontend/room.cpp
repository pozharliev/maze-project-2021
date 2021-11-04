#include "../../include/frontend/room.h"

Room::~Room()
{
    delete[] rightMaze;
    delete[] leftMaze;
    delete mazeTile;
    delete runeSprite;
    delete rune;
    delete runeTileSprite;
    delete runeTile;
    delete scroll;
    delete scrollDecal;
}

Room::Room(int mWidth, int mHeight)
{
    mazeWidth = mWidth;
    mazeHeight = mHeight;
    tileWidth = 13;
    tileHeight = 13;

    rightMaze = new CheckedMaze(mazeWidth, mazeHeight);
    rightMaze->checkMaze();
    leftMaze = new CheckedMaze(mazeWidth, mazeHeight);
    leftMaze->checkMaze();

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
            if (leftMaze->checkedMaze[i * mazeWidth + j] == '#')
            {
                rawMazeData << "1";
            }
            else if (leftMaze->checkedMaze[i * mazeWidth + j] == ' ')
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
    return (mazeOrientation == "left") ? leftMaze->checkedMaze[y * mazeWidth + x] : rightMaze->checkedMaze[y * mazeWidth + x];
}

void Room::DrawRoom(olc::PixelGameEngine *engine, std::string mazeOrientation)
{

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

                case 'P':
                    engine->DrawSprite(x * tileWidth, y * tileHeight, mazeTile);
                    engine->DrawDecal({x * tileWidth, y * tileHeight}, scrollDecal, {0.25f, 0.25f});
                    break;

                case 'D':
                    engine->DrawSprite(x * tileWidth, y * tileHeight, mazeTile);
                    engine->DrawDecal({x * tileWidth, y * tileHeight}, scrollDecal, {0.25f, 0.25f});
                    break;

                case 'S':
                    engine->DrawSprite(x * tileWidth, y * tileHeight, mazeTile);
                    engine->DrawDecal({x * tileWidth, y * tileHeight}, scrollDecal, {0.25f, 0.25f});
                    break;

                default:
                    break;
                }

                if (x == 1 && y == mazeHeight - 1)
                {
                    engine->DrawDecal({x * tileWidth, y * tileHeight}, runeTile);
                }

                if (x == 1 && y == mazeHeight - 1)
                {
                    engine->DrawDecal({x * tileWidth + 1.5f, y * tileHeight}, rune, {0.55f, 0.55f});
                }
            }
        }
    }
    else
    {
        for (int x = 0; x < mazeWidth; x++)
        {
            for (int y = 0; y < mazeHeight; y++)
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