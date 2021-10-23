#define OLC_PGE_APPLICATION
#define OLC_PGEX_TRANSFORMEDVIEW
#include "../../include/frontend/game.h"


//↓Start of PixelGameEngine functions-----------↓

  bool Game::OnUserCreate()
  { 

    tv = olc::TileTransformedView({ ScreenWidth(), ScreenHeight() }, { 1, 1 });
    object.pos = {3.0f, 3.0f};

    playerX = ScreenWidth() / 2;
    playerY = ScreenHeight() / 2;
    playerSpeed = PLAYER_SPEED;
    playerRadius = 5.0f;
    pauseMenuEnabled = false;
    mainMenuEnabled = true;
    optionsMenuEnabled = false;
    menuOption = 0;
    gameStarted = false;

    WorldMap =
      "#################################"
      "#s#         #         #         #"
      "# ### ##### ### ##### ### ##### #"
      "#   #     #   #     #   #     # #"
      "### ### ##### ### ##### ### ### #"
      "# #   #   #     #   #     #   # #"
      "# ### ### ### # ### ### # ### ###"
      "#   #   #   # #   #   # #   #   #"
      "### ### ### ##### ### ##### ### #"
      "###   #   #   #     #   ###   # #"
      "##### ### ### ### # ### ##### # #"
      "#       #   #   # #   #   #     #"
      "# ### # ### ### ##### ### ##### #"
      "#   # #   #   #   #     #   #   #"
      "### ##### ### ### ### # ### #####"
      "# #   # #   #   #   # #   #   # #"
      "# ### # ### ### ### ##### ### # #"
      "#   #     #   #   #   #     #   #"
      "### ### ##### ### ### ### # ### #"
      "###   #   # #   #   #   # #   # #"
      "##### ### # ### ### ### ##### # #"
      "#       #     #   #   #   #     #"
      "# ### # ### ##### ### ### ### # #"
      "#   # #   #   # #   #   #   # # #"
      "### ##### ### # ### ### ### ### #"
      "# #   # #   #     #   #   #   # #"
      "# ### # ### ### ##### ### ### ###"
      "#   #     #   #   # #   #   #   #"
      "### ### ##### ### # ### ### ### #"
      "# #   #   ###   #   # #   #   # #"
      "# ### ### ##### ### # ### ### # #"
      "#             #       ###       e"
      "#################################";

    worldSize = {33, 33};

    return true;
  }

  bool Game::OnUserUpdate(float fElapsedTime)
  {
    
    if (GetMouse(2).bPressed) tv.StartPan(GetMousePos());
    if (GetMouse(2).bHeld) tv.UpdatePan(GetMousePos());
    if (GetMouse(2).bReleased) tv.EndPan(GetMousePos());
    if (GetMouseWheel() > 0) tv.ZoomAtScreenPos(2.0f, GetMousePos());
    if (GetMouseWheel() < 0) tv.ZoomAtScreenPos(0.5f, GetMousePos());

    if(gameStarted)
    {
      startGame(fElapsedTime);
    }

    //Get the position of the player for both x and y
    

    //Clear the console

    // olc::vi2d topLeft = tv.GetTopLeftTile().max({0, 0});
    // olc::vi2d bottomRight = tv.GetBottomRightTile().min(worldSize);
    // olc::vi2d tile;

    // for(tile.y = topLeft.y; tile.y < bottomRight.y; tile.y++)
    // {
    //   for(tile.x = topLeft.x; tile.x < bottomRight.x; tile.x++)
    //   {
    //     if(WorldMap[tile.y * worldSize.x + tile.x] == '#')
    //     {
    //       tv.DrawRect(tile, {1.0f, 1.0f}, olc::WHITE);
    //       tv.DrawLine(tile, tile + olc::vf2d(1.0f, 1.0f), olc::WHITE);
    //       tv.DrawLine(tile + olc::vf2d(0.0f, 1.0f), tile + olc::vf2d(1.0f, 0.0f), olc::WHITE);
    //     }
    //   }
    // }
    
    //Draw the player character
    
    rect r = { {(ScreenWidth() / 2 - ScreenHeight() / 2), ScreenHeight() / 2 - 25.0f}, {6.0f, 50.0f} };
    rect border = {{(ScreenWidth() / 2 - ScreenHeight() / 2), 0}, {ScreenHeight(), ScreenHeight() - 1.0f}};

    if(pointCollRect(playerPos, r))
      tv.DrawRect(r.pos, r.size, olc::YELLOW);
    else
      tv.DrawRect(r.pos, r.size, olc::WHITE);

    tv.DrawRect(border.pos,border.size, olc::WHITE);

    if(pauseMenuEnabled){
      displayPauseMenu();
    }

    if(mainMenuEnabled){
      displayMainMenu();
    }

    if(optionsMenuEnabled){
      displayOptionsMenu();
    }

    return true;
  }

//↑End of PixelGameEngine functions-------------↑



//↓Start of Game mechanic functions-----------------------------↓

  bool Game::startGame(float fElapsedTime)
  {
    
    //start cutscene
    //enter dungeon - draw area, draw player, get input
    //start dungeon(floor,  keys) - draw area, draw player, get input

    //Listen for inputs from the player
    getInput(fElapsedTime);

    playerPos = {playerX, playerY};
    Clear(olc::BLACK);
    
    drawPlayer(playerX, playerY, playerRadius);
    return true;
  }

  bool Game::pointCollRect(const olc::vf2d& p, const rect& r)
  {
    return (p.x >= r.pos.x && p.y >= r.pos.y && p.x < r.pos.x + r.size.x && p.y < r.pos.y + r.size.y);
  }

  void Game::getInput(float elapsedTime)
  {
    if(GetKey(olc::LEFT).bHeld && playerX >= (ScreenWidth() / 2 - ScreenHeight() / 2) + playerRadius + 0.4f && pauseMenuEnabled == false && mainMenuEnabled == false){
      movePlayer(olc::LEFT, elapsedTime);
    }
    if(GetKey(olc::LEFT).bReleased){
        playerSpeed = PLAYER_SPEED;
    }

    if(GetKey(olc::RIGHT).bHeld  && playerX <= ScreenWidth() && pauseMenuEnabled == false && mainMenuEnabled == false){
      movePlayer(olc::RIGHT, elapsedTime);
    }
    if(GetKey(olc::RIGHT).bReleased){
        playerSpeed = PLAYER_SPEED;
    }

    if(GetKey(olc::UP).bHeld && playerY >= 0 && pauseMenuEnabled == false && mainMenuEnabled == false){
      movePlayer(olc::UP, elapsedTime);
    }
    if(GetKey(olc::UP).bReleased){
      playerSpeed = PLAYER_SPEED;
    }

    if(GetKey(olc::DOWN).bHeld && playerY <= ScreenHeight() && pauseMenuEnabled == false && mainMenuEnabled == false){
      movePlayer(olc::DOWN, elapsedTime);
    }
    if(GetKey(olc::DOWN).bReleased){
      playerSpeed = PLAYER_SPEED;
    }

    if(GetKey(olc::ESCAPE).bPressed && !mainMenuEnabled && !optionsMenuEnabled){
      if(!pauseMenuEnabled){
        pauseMenuEnabled = true;
      }
      else{
        pauseMenuEnabled = false;
      }
    }

    if(GetKey(olc::F4).bPressed){
      exit(0);
    }
  }

//↑End of Game mechanic functions-------------------------------↑



//↓Start of Player functions-----------------------------------------------↓

  void Game::movePlayer(olc::Key dir, float elapsedTime)
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

  void Game::drawPlayer(float playerX, float playerY, float playerRadius)
  {
    tv.DrawCircle(playerX, playerY, playerRadius, olc::RED);
  }

//↑End of Player functions-------------------------------------------------↑



//↓Start of Menu functions--------------------------↓

  bool Game::displayPauseMenu()
  {
    std::string menuOptionsArr[2] = {"Continue", "Quit To Menu"};
    Clear(olc::BLACK);
    int vSpacing = -16;

    for(int i = 0; i < 2; i++)
    {
      if(i == menuOption)
      {
        DrawString(ScreenWidth() / 2 - 56, ScreenHeight() / 2 + vSpacing, "-> " + menuOptionsArr[i], olc::DARK_GREY);
      } else {
        DrawString(ScreenWidth() / 2 - 32, ScreenHeight() / 2 + vSpacing, menuOptionsArr[i], olc::WHITE);
      }

      vSpacing += 32;
    }

    getMenuInput("pause");
    vSpacing = -16;
    return true;
  }

  bool Game::displayMainMenu()
  {
    std::string menuOptionsArr[3] = {"Start Game", "Options", "Quit Game"};
    Clear(olc::BLACK);
    int spacing = -32;

    for(int i = 0; i < 3; i++)
    {
      if(i == menuOption)
      {
        DrawString(ScreenWidth() / 2 - 64, ScreenHeight() / 2 + spacing, "-> " + menuOptionsArr[i], olc::DARK_GREY);
      } else {
        DrawString(ScreenWidth() / 2 - 40, ScreenHeight() / 2 + spacing, menuOptionsArr[i], olc::WHITE);
      }

      spacing += 32;
    }
    getMenuInput("main");
    spacing = -32;
    return true;
  }

  bool Game::displayOptionsMenu()
  {
    std::string menuOptionsArr[4] = {"Full Screen", "Sound", "Controls", "Back"};
    Clear(olc::BLACK);
    int spacing = -32;

    for(int i = 0; i < 4; i++)
    {
      if(i == menuOption)
      {
        DrawString(ScreenWidth() / 2 - 64, ScreenHeight() / 2 + spacing, "-> " + menuOptionsArr[i], olc::DARK_GREY);
      } else {
        DrawString(ScreenWidth() / 2 - 40, ScreenHeight() / 2 + spacing, menuOptionsArr[i], olc::WHITE);
      }

      spacing += 32;
    }
    getMenuInput("options");
    spacing = -32;
    return true;
  }

  void Game::getMenuInput(std::string menuType)
  {
    if(menuType == "main")
    {
      if(GetKey(olc::DOWN).bPressed)
      {
        if(menuOption == 2)
        {
          menuOption = 0;
        } else {
          menuOption+= 1;
        }
      }

      if(GetKey(olc::UP).bPressed)
      {
        if(menuOption == 0)
        {
          menuOption = 2;
        } else {
          menuOption -= 1;
        }
      }

      if(GetKey(olc::ENTER).bPressed)
      {
        if(menuOption == 0){
          mainMenuEnabled = false;
          gameStarted = true;
          menuOption = 0; // reset the selected option after quitting the menu
        }
        if(menuOption == 1){
          optionsMenuEnabled = true;
          mainMenuEnabled = false;
          menuOption = 0;
        }
        if(menuOption == 2){
          exit(0);
        }
      }

    }

    if(menuType == "pause")
    {
      if(GetKey(olc::DOWN).bPressed)
      {
        if(menuOption == 1)
        {
          menuOption = 0;
        } else {
        menuOption+= 1;
        }
      }

      if(GetKey(olc::UP).bPressed)
      {
        if(menuOption == 0)
        {
          menuOption = 1;
        } else {
          menuOption -= 1;
        }
      }

      if(GetKey(olc::ENTER).bPressed)
      {
        if(menuOption == 0){
          pauseMenuEnabled = false;
          menuOption = 0; // reset the selected option after quitting the menu
        }
        if(menuOption == 1){
          mainMenuEnabled = true;
          pauseMenuEnabled = false;
        }
      }
    }
    
    if(menuType == "options")
    {
      if(GetKey(olc::DOWN).bPressed)
      {
        if(menuOption == 3)
        {
          menuOption = 0;
        } else {
          menuOption+= 1;
        }
      }

      if(GetKey(olc::UP).bPressed)
      {
        if(menuOption == 0)
        {
          menuOption = 3;
        } else {
          menuOption -= 1;
        }
      }

      if(GetKey(olc::ENTER).bPressed)
      {
        if(menuOption == 0){
          if(fullScreen == false){
            writeFile.open ("saveFile.txt", std::ofstream::out | std::ofstream::trunc);
            writeFile << "true";
            writeFile.close();
          }
          else{
            writeFile.open ("saveFile.txt", std::ofstream::out | std::ofstream::trunc);
            writeFile << "false";
            writeFile.close();
          }
        }
        if(menuOption == 1){
          // sound
        }
        if(menuOption == 2){
          // controls
        }
        if(menuOption == 3){
          optionsMenuEnabled = false;
          mainMenuEnabled = true;
          menuOption = 0;
        }
      }

    }
  }

//↑End of Menu functions---------------------------↑