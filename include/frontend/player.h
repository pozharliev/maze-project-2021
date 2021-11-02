#pragma once

#include "../backend/libs.h"

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
    enum PLAYER_DIRS{
        UP,
        DOWN,
        LEFT,
        RIGHT
    };
    PLAYER_DIRS playerDir;

    olc::Renderable* playerAnimSpritesheet;
    olc::AnimatedSprite* Animator;

private:
    // PlayerAnimator* playerAnimator;
    // olc::Sprite* currentAnimSprite;
    // olc::Decal* currentAnim;
    // PlayerAnimator::AnimationData animationData;

    void setUpAnimations();

public:

    ~Player();

    void innitPlayer();

    void movePlayer(olc::PixelGameEngine* engine, olc::Key dir, float elapsedTime);

    void drawPlayer(olc::PixelGameEngine *engine, float elapsedTime);

    void getInput();
};