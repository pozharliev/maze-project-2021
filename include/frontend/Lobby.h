#pragma once

#include "../backend/libs.h"

class Lobby
{
public:
  struct rect
  {
    olc::vf2d pos;
    olc::vf2d size;
  };

  rect r;

public:
  void drawLobby(olc::PixelGameEngine *engine);
};