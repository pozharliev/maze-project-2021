#include "../../include/frontend/player.h"

Player::~Player()
{
  delete playerSprite;
  delete playerDecal;
}

void Player::innitPlayer()
{
  playerAnimator = new PlayerAnimator;
  playerSprite = new olc::Sprite("public/Player_Anim_Spritesheet.png");
  playerDecal = new olc::Decal(playerSprite);
  animationData.sourceSize = {0.0f, 0.0f};
  animationData.sourcePos = {0.0f, 0.0f};

  playerAnimator->setParams(0.125f, playerSprite->width, playerSprite->height, 12, 4, 48);
}

void Player::movePlayer(olc::PixelGameEngine* engine, olc::Key dir, float elapsedTime)
  {
    switch(dir)
    {
      case olc::LEFT:
        playerVelX = -playerSpeed;
        playerX += playerVelX * elapsedTime;
        break;

      case olc::RIGHT:
        playerVelX = playerSpeed;
        playerX += playerVelX * elapsedTime;
        break;

      case olc::UP:
        playerVelY = -playerSpeed;
        playerY += playerVelY * elapsedTime;
        break;

      case olc::DOWN:
        playerVelY = playerSpeed;
        playerY += playerVelY * elapsedTime;
        break;

      default:
      break;
    }

    newPlayerPosX = playerX + playerVelX * elapsedTime;
    newPlayerPosY = playerY + playerVelY * elapsedTime;

    animationData = playerAnimator->getInfo(elapsedTime);
  }

void Player::drawPlayer(olc::PixelGameEngine* engine)
  {
    olc::vf2d playerSpriteSize = {31.75f, 31.25f};
    engine->DrawPartialDecal(playerPos, playerSpriteSize, playerDecal, animationData.sourcePos, animationData.sourceSize);
  }
