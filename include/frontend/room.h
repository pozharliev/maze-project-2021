#pragma once

#include "../backend/libs.h"
#include "../backend/checkedMaze.h"

class Room
{

    private:
        int mazeWidth, mazeHeight;
        CheckedMaze* roomMaze;

        float playerPosX;
        float playerPosY;
        

    public:
        Room(int mWidth, int mHeight);
        std::fstream rawMazeData;
        std::string line;

        int tileWidth;
        int tileHeight;

        int visibleTilesX;
        int visibleTilesY;

        float cameraPosX;
	    float cameraPosY;
        float offsetX;
        float offsetY;

    private:
        void generateRoom();
    
    public:
        char getTile(int x, int y);
        void DrawRoom(olc::PixelGameEngine* engine);
};