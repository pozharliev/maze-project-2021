#pragma once

#include "../backend/libs.h"

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
  void drawLobby(olc::PixelGameEngine *engine);

private:
  void initLobby();
};