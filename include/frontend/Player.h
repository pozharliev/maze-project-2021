#pragma once

#include "../backend/libs.h"

#define PLAYER_SPEED 60.0f

class Player{

    public:
        float playerX;
        float playerY;
        olc::vf2d playerPos;
        float playerSpeed;
        float playerRadius;

    public:

        void movePlayer(olc::PixelGameEngine* engine, olc::Key dir, float elapsedTime);
      
        void drawPlayer(olc::PixelGameEngine* engine);

        void getInput();

};