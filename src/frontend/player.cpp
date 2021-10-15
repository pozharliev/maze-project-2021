#define OLC_PGE_APPLICATION

#include "../../include/frontend/player.h"

bool Player::OnUserCreate()
{
  // Called once at the start, so create things here
  playerX = ScreenWidth() / 2;
  playerY = ScreenHeight() / 2;
  playerSpeed = PLAYER_SPEED;

  return true;
}

bool Player::OnUserUpdate(float fElapsedTime)
{
  // called once per frame
  if(GetKey(olc::LEFT).bHeld){
    playerX -= playerSpeed * fElapsedTime;
  }

  if(GetKey(olc::RIGHT).bHeld){
    playerX += playerSpeed * fElapsedTime;
  }

  if(GetKey(olc::UP).bHeld){
    playerY -= playerSpeed * fElapsedTime;
  }

  if(GetKey(olc::DOWN).bHeld){
    playerY += playerSpeed * fElapsedTime;
  }

  Clear(olc::BLACK);
  
  FillCircle(playerX, playerY, 5, olc::RED);

  return true;
}