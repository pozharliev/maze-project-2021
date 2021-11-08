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
        olc::Sprite* pathTile;

    public:
        Room(int mWidth, int mHeight);
        std::fstream rawMazeData;
        std::string line;

        int tileWidth;
        int tileHeight;
        bool roomEnriched;

        olc::Sprite* platformSprite;
        olc::Sprite* platformSpriteRight;
        olc::Sprite* runeSprite;
        olc::Decal* rune;
        olc::Sprite* runeSpriteIcon;
        olc::Decal* runeIcon;
        olc::Sprite* scrollDashSprite;
        olc::Decal* scrollDash;
        bool leftRunePickedUp;
        bool rightRunePickedUp;
        bool pathEnabled;

        olc::Sprite* runeTileSprite;

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

        bool sound;

    private:
        void generateRoom();
    
    public:
        ~Room();
        void setUpScrollAnimations();
        char getTile(std::string mazeOrientation, int x, int y);
        char getPathTile(std::string mazeOrientation, int x, int y);
        void DrawRoom(olc::PixelGameEngine* engine, std::string mazeOrientation);
};