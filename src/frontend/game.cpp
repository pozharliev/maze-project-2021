#define OLC_PGE_APPLICATION
#define OLC_PGEX_TRANSFORMEDVIEW
#include "../../include/frontend/game.h"


  // Function called once at the start of the program
bool Game::OnUserCreate()
{ 
  cMap.initMap(1);

  tv = olc::TileTransformedView({ ScreenWidth(), ScreenHeight() }, { 1, 1 });
  object.pos = {3.0f, 3.0f};

  playerX = ScreenWidth() / 2;
  playerY = ScreenHeight() / 2;
  playerSpeed = PLAYER_SPEED;

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
  tv.DrawCircle(playerX, playerY, 5, olc::RED);
  
  rect r = { {100.0f, 100.0f}, {50.0f, 50.0f} };
  rect border = {{84, 0}, {ScreenWidth() - 169.0f, ScreenHeight() - 1.0f}};

  if(pointCollRect(playerPos, r))
    tv.DrawRect(r.pos, r.size, olc::YELLOW);
  else
    tv.DrawRect(r.pos, r.size, olc::WHITE);

  return true;
}

bool Game::pointCollRect(const olc::vf2d& p, const rect& r)
{
  return (p.x >= r.pos.x && p.y >= r.pos.y && p.x < r.pos.x + r.size.x && p.y < r.pos.y + r.size.y);
}

void Game::getInput(float elapsedTime)
{
  if(GetKey(olc::LEFT).bHeld && playerX >= 0){
    movePlayer(olc::LEFT, elapsedTime);
  }
  if(GetKey(olc::LEFT).bReleased){
      playerSpeed = PLAYER_SPEED;
  }

  if(GetKey(olc::RIGHT).bHeld  && playerX <= ScreenWidth()){
    movePlayer(olc::RIGHT, elapsedTime);
  }
  if(GetKey(olc::RIGHT).bReleased){
      playerSpeed = PLAYER_SPEED;
  }

  if(GetKey(olc::UP).bHeld && playerY >= 0){
    movePlayer(olc::UP, elapsedTime);
  }
  if(GetKey(olc::UP).bReleased){
    playerSpeed = PLAYER_SPEED;
  }

  if(GetKey(olc::DOWN).bHeld && playerY <= ScreenHeight()){
    movePlayer(olc::DOWN, elapsedTime);
  }
  if(GetKey(olc::DOWN).bReleased){
    playerSpeed = PLAYER_SPEED;
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


Map::Map(){
    initMap(1);
}

bool Map::OnUserCreate()
{
    border = {{84, 0}, {ScreenWidth() - 169.0f, ScreenHeight() - 1.0f}};
    return true;
}

bool Map::OnUserUpdate(float fElapsedTime)
{
    initMap(1);
    return true;
}

void Map::initMap(int level)
{
    drawBorder();
}

void Map::drawBorder()
{
    DrawRect(border.pos,border.size, olc::WHITE);
}