#pragma once
#include "../backend/libs.h"
#include <cmath>

class PlayerAnimator
{
    private:
        float mInterval;
        int mTotalWidth;
        int mTotalHeight;
        int mTileCountX;
        int mTileCountY;
        int mTotalTileCount;

        float currentTime;
        int currentTile;

        struct playerAnimsSprites{
            olc::Sprite *playerUp;
            olc::Sprite *playerDown;
            olc::Sprite *playerLeft;
            olc::Sprite *playerRight;
        };


    public:
        struct AnimationData{
            olc::vf2d sourcePos;
            olc::vf2d sourceSize;
        };

        playerAnimsSprites mPlayerAnimSprites;

    public:
        ~PlayerAnimator();

        void setParams(float interval, int totalWidth, int totalHeight, int tileCountX, int tileCountY, int totalTileCount);

        AnimationData getInfo(float elapsedTime);
        
};