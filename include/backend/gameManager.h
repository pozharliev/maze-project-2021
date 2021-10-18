#pragma once

#include "../../libs/olcPixelGameEngine.h"
#include "../../libs/olcPGEX_TransformedView.h"


class GameManager : public olc::PixelGameEngine
{

    private:
        bool OnUserCreate() override;

        bool OnUserUpdate(float fElapsedTime) override;
};