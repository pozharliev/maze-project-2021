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
    bool optionsMenuEnabled;
    int menuOption;
    bool gameStarted;
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

    //↓Start of PixelGameEngine functions---------------↓

      bool OnUserCreate() override;

      bool OnUserUpdate(float fElapsedTime) override;

    //↑End of PixelGameEngine functions-----------------↑



    //↓Start of Game mechanic functions------------------------↓

      bool startGame(float fElapsedTime);
      
      bool pointCollRect(const olc::vf2d& p, const rect& r);

      void getInput(float elapsedTime);

    //↑End of Game mechanic functions--------------------------↑

    

    //↓Start of Player functions-------------------------------------------↓

      void movePlayer(olc::Key dir, float elapsedTime);
      
      void drawPlayer(float playerX, float playerY, float playerRadius);

    //↑End of Player functions---------------------------------------------↑


      
    //↓Start of Menu functions-------------------↓

      bool displayPauseMenu();

      bool displayMainMenu();

      bool displayOptionsMenu();

      void getMenuInput(std::string menuType);

    //↑End of Menu functions---------------------↑
};
