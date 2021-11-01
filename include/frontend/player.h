#pragma once

#include "../backend/libs.h"
#include "playerAnimator.h"

class Player
{

public:
    float playerX;
    float playerY;
    float newPlayerPosX;
    float newPlayerPosY;
    olc::vf2d playerPos;
    float playerSpeed;
    float playerVelX;
    float playerVelY;
    float playerRadius;

private:
    PlayerAnimator* playerAnimator;
    olc::Sprite* currentAnimSprite;
    olc::Decal* currentAnim;
    PlayerAnimator::AnimationData animationData;

public:

    ~Player();

    void innitPlayer();

    void movePlayer(olc::PixelGameEngine* engine, olc::Key dir, float elapsedTime);

    void drawPlayer(olc::PixelGameEngine *engine);

    void getInput();
};