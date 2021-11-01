#include "../../include/frontend/player.h"

void Player::innitPlayer()
{
  playerAnimator = new PlayerAnimator;
  currentAnimSprite = new olc::Sprite("public/Player_Up_Anim.png");
  currentAnim = new olc::Decal(currentAnimSprite);
  animationData.sourceSize = {0.0f, 0.0f};
  animationData.sourcePos = {0.0f, 0.0f};

  playerAnimator->setParams(0.07f, currentAnimSprite->width, currentAnimSprite->height, 12, 1, 12);
}

void Player::movePlayer(olc::PixelGameEngine* engine, olc::Key dir, float elapsedTime)
  {
    switch(dir)
    {
      case olc::LEFT:
        currentAnim = new olc::Decal(playerAnimator->mPlayerAnimSprites.playerLeft);
        playerVelX = -playerSpeed;
        playerX += playerVelX * elapsedTime;
        break;

      case olc::RIGHT:
        currentAnim = new olc::Decal(playerAnimator->mPlayerAnimSprites.playerRight);
        playerVelX = playerSpeed;
        playerX += playerVelX * elapsedTime;
        break;

      case olc::UP:
        currentAnim = new olc::Decal(playerAnimator->mPlayerAnimSprites.playerUp);
        playerVelY = -playerSpeed;
        playerY += playerVelY * elapsedTime;
        break;

      case olc::DOWN:
        currentAnim = new olc::Decal(playerAnimator->mPlayerAnimSprites.playerDown);
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
    engine->DrawPartialDecal(playerPos, playerSpriteSize, currentAnim, animationData.sourcePos, animationData.sourceSize);
  }
