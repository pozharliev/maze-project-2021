#pragma once

#include "../backend/libs.h"
#include "../frontend/player.h"
#include "../frontend/room.h"

class Lobby
{

private:
  int lobbyWidth;
  int lobbyHeight;
  std::string lobbyRawData;

  int tileWidth;
  int tileHeight;

  int visibleTilesX;
  int visibleTilesY;

  int mazePlayerPosX;
  int mazePlayerPosY;

public:

  Room* room;

  int thisLobbyCount;

  struct rect
  {
    olc::vf2d pos;
    olc::vf2d size;
  };

  rect stairCase;
  
  rect r;
  bool inMaze;
  olc::Sprite *lobbyRoom;
  olc::Sprite *lobbyForegroundSprite;
  olc::Decal *lobbyForeground;
  olc::Sprite *lobbyRays;
  olc::Decal *lobbyRaysDecal;
  bool leftMazeEnter;
  bool rightMazeEnter;
  bool inLeftMaze;
  bool inRightMaze;
  enum MAZE_TYPE{
    LEFT,
    RIGHT
  };
  MAZE_TYPE currentMaze;

public:
  Lobby(int count);
  ~Lobby();
  char getTile(int x, int y);

  void drawLobby(olc::PixelGameEngine* engine, Player* player);

  void drawLobbyForeground(olc::PixelGameEngine* engine);

  bool hallCollision(Player* player, rect roomLeft);

  bool pointCollRect(const olc::vf2d &p, const rect &r);

private:
  void initLobby();
};