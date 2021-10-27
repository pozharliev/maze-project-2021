#include "../../include/frontend/room.h"

Room::Room(int mWidth, int mHeight)
{
    mazeWidth = mWidth;
    mazeHeight = mHeight;
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

//# - 1
//" " - 0