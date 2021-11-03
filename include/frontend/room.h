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
        olc::Sprite* mazeTile;

    public:
        Room(int mWidth, int mHeight);
        std::fstream rawMazeData;
        std::string line;

        int tileWidth;
        int tileHeight;

        olc::Sprite* runeSprite;
        olc::Decal* rune;

        olc::Sprite* runeTileSprite;
        olc::Decal* runeTile;

        
    private:
        void generateRoom();
    
    public:
        ~Room();
        char getTile(int x, int y);
        void DrawRoom(olc::PixelGameEngine* engine);
};