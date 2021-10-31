#include "../../include/frontend/player.h"

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
  }

void Player::drawPlayer(olc::PixelGameEngine* engine)
  {
    engine->DrawCircle(playerX, playerY, playerRadius, olc::RED);
  }
