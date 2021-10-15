#define OLC_PGE_APPLICATION

#include "../../include/frontend/player.h"

  // Function is called once at the start
bool Player::OnUserCreate()
{
  playerX = ScreenWidth() / 2;
  playerY = ScreenHeight() / 2;
  playerSpeed = PLAYER_SPEED;

  return true;
}

  // Function is called once every frame
bool Player::OnUserUpdate(float fElapsedTime) 
{
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