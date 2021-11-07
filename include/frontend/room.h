#pragma once

#include "../backend/libs.h"
#include "../backend/checkedMaze.h"

class Room
{

    private:
        int mazeWidth, mazeHeight;
        CheckedMaze* leftMaze;
        CheckedMaze* rightMaze;

        float playerPosX;
        float playerPosY;
        olc::Sprite* mazeTile;

    public:
        Room(int mWidth, int mHeight);
        std::fstream rawMazeData;
        std::string line;

        int tileWidth;
        int tileHeight;
        bool roomEnriched;

        olc::Sprite* runeSprite;
        olc::Decal* rune;
        bool leftRunePickedUp;
        bool rightRunePickedUp;

        olc::Sprite* runeTileSprite;
        olc::Decal* runeTile;

        struct item{
            int x;
            int y;
            std::string type;
            bool pickedUp;
        };
        std::vector<item> items_vec;

        olc::Sprite* scroll;
        olc::Decal* scrollDecal;
        olc::Renderable* scrollAnimSpritesheet;
        olc::AnimatedSprite* scrollAnimator;

        

    private:
        void generateRoom();
    
    public:
        ~Room();
        void setUpScrollAnimations();
        char getTile(std::string mazeOrientation, int x, int y);
        void DrawRoom(olc::PixelGameEngine* engine, std::string mazeOrientation);
};