#define OLC_PGE_APPLICATION
#define OLC_PGEX_TRANSFORMEDVIEW
#include "../../include/frontend/game.h"


  // Function called once at the start of the program
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
  menuOption = 0;

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

  // Function called once every frame
bool Game::OnUserUpdate(float fElapsedTime)
{
  if (GetMouse(2).bPressed) tv.StartPan(GetMousePos());
	if (GetMouse(2).bHeld) tv.UpdatePan(GetMousePos());
	if (GetMouse(2).bReleased) tv.EndPan(GetMousePos());
	if (GetMouseWheel() > 0) tv.ZoomAtScreenPos(2.0f, GetMousePos());
	if (GetMouseWheel() < 0) tv.ZoomAtScreenPos(0.5f, GetMousePos());

  //Listen for inputs from the player
  getInput(fElapsedTime);

  //Get the position of the player for both x and y
  playerPos = {playerX, playerY};

  //Clear the console
  Clear(olc::BLACK);

  olc::vi2d topLeft = tv.GetTopLeftTile().max({0, 0});
  olc::vi2d bottomRight = tv.GetBottomRightTile().min(worldSize);
  olc::vi2d tile;

  for(tile.y = topLeft.y; tile.y < bottomRight.y; tile.y++)
  {
    for(tile.x = topLeft.x; tile.x < bottomRight.x; tile.x++)
    {
      if(WorldMap[tile.y * worldSize.x + tile.x] == '#')
      {
        tv.DrawRect(tile, {1.0f, 1.0f}, olc::WHITE);
        tv.DrawLine(tile, tile + olc::vf2d(1.0f, 1.0f), olc::WHITE);
        tv.DrawLine(tile + olc::vf2d(0.0f, 1.0f), tile + olc::vf2d(1.0f, 0.0f), olc::WHITE);
      }
    }
  }
  
  //Draw the player character
  tv.DrawCircle(playerX, playerY, playerRadius, olc::RED);
  
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

  if(GetKey(olc::ESCAPE).bPressed){
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

bool Game::displayPauseMenu(){
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

bool Game::displayMainMenu(){
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
      }
      if(menuOption == 1){
        // settings
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
      }
      if(menuOption == 1){
        mainMenuEnabled = true;
        pauseMenuEnabled = false;
      }
    }

  }

}