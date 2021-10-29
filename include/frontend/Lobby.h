#pragma once

#include "../backend/libs.h"
#include "../frontend/Player.h"
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

public:
  struct rect
  {
    olc::vf2d pos;
    olc::vf2d size;
  };

  rect r;

public:
  void drawLobby(olc::PixelGameEngine* engine, Player* player, Room* room);


private:
  void initLobby();

  void hallCollision(olc::PixelGameEngine* engine, Player* player, Room* room);

  bool pointCollRect(const olc::vf2d &p, const rect &r);
};