#pragma once

#include "../backend/libs.h"

class Lobby : public olc::PixelGameEngine
{
    public:
    struct rect{
      olc::vf2d pos;
      olc::vf2d size;
    };

    public:
        void drawLobby();
};