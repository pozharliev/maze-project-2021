#pragma once

#include "../../libs/olcPixelGameEngine.h"
#include "../../libs/olcPGEX_TransformedView.h"

class Map : public olc::PixelGameEngine
{

    public:
        Map();
        void initMap(int level);

    private:
        void drawBorder();

        bool OnUserCreate() override;

        bool OnUserUpdate(float fElapsedTime) override;

    private:
        struct rect{
            olc::vf2d pos;
            olc::vf2d size;
        };
        rect border;
};