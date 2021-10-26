#include "../../include/frontend/Player.h"

void Player::movePlayer(olc::PixelGameEngine* engine, olc::Key dir, float elapsedTime)
  {
    switch(dir)
    {
      case olc::LEFT: 
        playerX -= playerSpeed * elapsedTime;

        if(playerSpeed <= 100.0f){
          playerSpeed += 0.02f;
        }
        break;

      case olc::RIGHT:
        playerX += playerSpeed * elapsedTime;

        if(playerSpeed <= 100.0f){
            playerSpeed += 0.02f;
        }
        break;

      case olc::UP:
        playerY -= playerSpeed * elapsedTime;

        if(playerSpeed <= 100.0f){
          playerSpeed += 0.02f;
        }
        break;

      case olc::DOWN:
        playerY += playerSpeed * elapsedTime;

        if(playerSpeed <= 100.0f){
          playerSpeed += 0.02f;
        }
        break;

      default:
      break;
    }
  }

void Player::drawPlayer(olc::PixelGameEngine* engine)
  {
    engine->DrawCircle(playerX, playerY, playerRadius, olc::RED);
  }
