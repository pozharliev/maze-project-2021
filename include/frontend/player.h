#pragma once

#include "../backend/libs.h"

 /* @file player.h
 *
 * @brief Declaration of the Player class.
 */

/**
 * @brief The Player class handles everything connected to the player, without the collisions.
 */

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
    /**
    * @brief Extracts parts of the PlayerAnimSpritesheet file and combines them in animations.
    **/
    void setUpAnimations();

public:
    ~Player();

    /**
    * @brief Extracts parts of the PlayerAnimSpritesheet file and combines them in animations.
    **/
    void innitPlayer();

    /**
    * @brief Based on the user input, changes the position of the player and predicts the future position,
    * @brief which is later on handled by the collisions.
    * 
    * @param[in] engine
    * @param[in] direction
    * @param[in] elapsedTime
    * 
    **/
    void movePlayer(olc::PixelGameEngine *engine, olc::Key dir, float elapsedTime);
    
    /**
    * @brief Displays the player.
    * @param[in] engine
    * @param[in] elapsedTime
    **/
    void drawPlayer(olc::PixelGameEngine *engine, float elapsedTime);

    /**
    * @brief Draws atmoshperic fog around the player.
    **/
    void drawPlayerVignette(olc::PixelGameEngine *engine);
};