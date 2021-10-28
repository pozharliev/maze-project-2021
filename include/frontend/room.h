#pragma once

#include "../backend/libs.h"
#include "../backend/checkedMaze.h"

class Room
{

    private:
        int mazeWidth, mazeHeight;
        CheckedMaze* roomMaze;

        int tileWidth;
        int tileHeight;
        

    public:
        Room(int mWidth, int mHeight);
        std::fstream rawMazeData;
        std::string line;

        int visibleTilesX;
        int visibleTilesY;

        float CameraPosX;
	    float CameraPosY;
        float offsetX;
        float offsetY;




    public:
        void generateRoom();

        void DrawRoom(olc::PixelGameEngine* engine);
};