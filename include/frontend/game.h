#pragma once

#include "../../libs/olcPixelGameEngine.h"
#include "../../libs/olcPGEX_TransformedView.h"
#include <string>

#define PLAYER_SPEED 60.0f

class Game : public olc::PixelGameEngine
{

  private:
    olc::TileTransformedView tv;
    float playerX;
    float playerY;
    olc::vf2d playerPos;
    float playerSpeed;
    float playerRadius;
    bool pauseMenuEnabled;
    bool mainMenuEnabled;
    int menuOption;
    struct rect{
      olc::vf2d pos;
      olc::vf2d size;
    };
    struct worldObj{
      olc::vf2d pos;
      olc::vf2d vel;
      float radius;
    };
    worldObj object;
    olc::vi2d worldSize;
    std::string WorldMap;

  public:
    bool OnUserCreate() override;

    bool OnUserUpdate(float fElapsedTime) override;
    
    bool pointCollRect(const olc::vf2d& p, const rect& r);

    void getInput(float elapsedTime);

    void movePlayer(olc::Key dir, float elapsedTime);

    bool displayPauseMenu();

    bool displayMainMenu();

    void getMenuInput(std::string menuType);

};