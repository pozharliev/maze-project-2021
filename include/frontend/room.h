#pragma once

#include "../backend/libs.h"
#include "../backend/checkedMaze.h"

class Room
{

    private:
        int mazeWidth, mazeHeight;
        CheckedMaze* roomMaze;

    public:
        Room(int mWidth, int mHeight);
        std::fstream rawMazeData;
        std::string line;


    public:
        void generateRoom();
};