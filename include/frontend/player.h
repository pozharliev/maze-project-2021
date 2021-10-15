#pragma once

#include "../../libs/olcPixelGameEngine.h"

#define PLAYER_SPEED 30

class Player : public olc::PixelGameEngine
{
  public:
    bool OnUserCreate() override;

    bool OnUserUpdate(float fElapsedTime) override;

  private:
    float playerX;
    float playerY;
    int playerSpeed;
};