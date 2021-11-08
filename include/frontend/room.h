#pragma once

#include "../backend/libs.h"
#include "../backend/checkedMaze.h"

class Room
{

private:
    int mazeWidth, mazeHeight;
    CheckedMaze *leftMaze;
    CheckedMaze *rightMaze;

    float playerPosX;
    float playerPosY;
    olc::Sprite *mazeTile;
    olc::Sprite *pathTile;

public:
    Room(int mWidth, int mHeight);
    std::fstream rawMazeData;
    std::string line;

    int tileWidth;
    int tileHeight;
    bool roomEnriched;

    olc::Sprite *platformSprite;
    olc::Sprite *platformSpriteRight;
    olc::Sprite *runeSprite;
    olc::Decal *rune;
    olc::Sprite *runeSpriteIcon;
    olc::Decal *runeIcon;
    olc::Sprite *scrollDashSprite;
    olc::Decal *scrollDash;
    bool leftRunePickedUp;
    bool rightRunePickedUp;
    bool pathEnabled;

    olc::Sprite *runeTileSprite;

    struct item
    {
        int x;
        int y;
        std::string type;
        bool pickedUp;
    };
    std::vector<item> items_vec;

    olc::Sprite *scroll;
    olc::Decal *scrollDecal;
    olc::Renderable *scrollAnimSpritesheet;
    olc::AnimatedSprite *scrollAnimator;

    bool sound;

private:
    /**
    * @brief Generates the two mazes in the room, based off of CheckedMaze class
    * @brief and writes the data to .maze files.
    **/
    void generateRoom();

public:
    ~Room();
    /**
    * @brief Extracts parts of the ScrollAnimSpritesheet file and combines them in animations.
    **/
    void setUpScrollAnimations();

    /**
    * @brief Returns the symbol from the desired maze(left or right) on x and y coordinates.
    **/
    char getTile(std::string mazeOrientation, int x, int y);
    /**
    * @brief Returns the symbol from the desired solved maze(left or right) on x and y coordinates.
    **/
    char getPathTile(std::string mazeOrientation, int x, int y);
    /**
    * @brief Displays the maze.
    **/
    void DrawRoom(olc::PixelGameEngine *engine, std::string mazeOrientation);
};