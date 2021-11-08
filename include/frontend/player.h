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
    enum PLAYER_DIRS
    {
        UP,
        DOWN,
        LEFT,
        RIGHT,
        NONE
    };
    PLAYER_DIRS playerDir;
    bool firstPlayerMove;
    bool dashing;
    struct inventory
    {
        bool speedScroll;
        bool dashScroll;
        bool pathScroll;
        int runes;
    };
    inventory playerInv;

    olc::Renderable *playerAnimSpritesheet;
    olc::AnimatedSprite *Animator;
    olc::Sprite *playerVignette;
    olc::Decal *playerVignetteDecal;

private:
    void setUpAnimations();

public:
    ~Player();

    void innitPlayer();

    void movePlayer(olc::PixelGameEngine *engine, olc::Key dir, float elapsedTime);

    void drawPlayer(olc::PixelGameEngine *engine, float elapsedTime);

    void drawPlayerVignette(olc::PixelGameEngine *engine);

    void getInput();
};