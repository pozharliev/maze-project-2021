#pragma once

#include "../frontend/map.h"


class GameManager : public olc::PixelGameEngine
{

    public:
        Map m_Map;

    public:
        GameManager();

    private:
        bool OnUserCreate() override;

        bool OnUserUpdate(float fElapsedTime) override;
};