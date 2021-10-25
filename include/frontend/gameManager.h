#pragma once

#include "Lobby.h"
#include "Player.h"

class GameManager : public olc::PixelGameEngine
{
    public:
        Player* player;
        Lobby* lobby;

    public:
        GameManager();

    private:
        bool OnUserCreate() override;

        bool OnUserUpdate(float fElapsedTime) override;
};