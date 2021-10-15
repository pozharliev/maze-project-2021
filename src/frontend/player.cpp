#define OLC_PGE_APPLICATION

#include "../../include/frontend/player.h"

  // Function called once at the start of the program
bool Player::OnUserCreate()
{
  
  playerX = ScreenWidth() / 2;
  playerY = ScreenHeight() / 2;
  playerSpeed = PLAYER_SPEED;

  return true;
}

  // Function called once every frame
bool Player::OnUserUpdate(float fElapsedTime)
{
  
  //Listen for inputs from the player

  if(GetKey(olc::LEFT).bHeld && playerX >= 0){
    playerX -= playerSpeed * fElapsedTime;
  }

  if(GetKey(olc::RIGHT).bHeld  && playerX <= ScreenWidth()){
    playerX += playerSpeed * fElapsedTime;
  }

  if(GetKey(olc::UP).bHeld && playerY >= 0){
    playerY -= playerSpeed * fElapsedTime;
  }

  if(GetKey(olc::DOWN).bHeld && playerY <= ScreenHeight()){
    playerY += playerSpeed * fElapsedTime;
  }

  Clear(olc::BLACK);
  
  //Draw the player character

  FillCircle(playerX, playerY, 5, olc::RED);

  return true;
}
