#pragma once

#include "../backend/libs.h"

class Player
{

public:
    float playerX;
    float playerY;
    float newPlayerPosX
    float newPlayerPosY;
    olc::vf2d playerPos;
    float playerSpeed;
    float playerRadius;

public:
    void movePlayer(olc::PixelGameEngine *engine, olc::Key dir, float elapsedTime);

    void drawPlayer(olc::PixelGameEngine *engine);

    void getInput();
};