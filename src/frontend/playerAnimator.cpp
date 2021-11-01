#include "../../include/frontend/playerAnimator.h"

PlayerAnimator::~PlayerAnimator()
{
    delete mPlayerAnimSprites.playerUp;
    delete mPlayerAnimSprites.playerDown;
    delete mPlayerAnimSprites.playerLeft;
    delete mPlayerAnimSprites.playerRight;
}

void PlayerAnimator::setParams(float interval, int totalWidth, int totalHeight, int tileCountX, int tileCountY, int totalTileCount)
{
    mInterval = interval;
	mTotalWidth = totalWidth;
	mTotalHeight = totalHeight;
	mTileCountX = tileCountX;
	mTileCountY = tileCountY;
	mTotalTileCount = totalTileCount;
    currentTime = 0.0f;
    currentTile = 0;

    mPlayerAnimSprites.playerUp = new olc::Sprite("public/Player_Up_Anim.png");
    mPlayerAnimSprites.playerDown = new olc::Sprite("public/Player_Down_Anim.png");
    mPlayerAnimSprites.playerLeft = new olc::Sprite("public/Player_Left_Anim.png");
    mPlayerAnimSprites.playerRight = new olc::Sprite("public/Player_Right_Anim.png");

}

PlayerAnimator::AnimationData PlayerAnimator::getInfo(float elapsedTime)
{
    currentTime += elapsedTime;

    if(currentTime >= mInterval)
    {
        currentTime = 0.0f;
        currentTile++;
    }

    if(currentTile >= mTotalTileCount)
    {
        currentTile = 0;
    }

    AnimationData data;

    data.sourceSize.x = (float)mTotalWidth / (float)mTileCountX;
    data.sourceSize.y = (float)mTotalHeight / (float)mTileCountY;

    data.sourcePos.x = (currentTile % mTileCountX) * data.sourceSize.x;
    data.sourcePos.y = floorf((float)currentTile / (float)mTileCountX) * data.sourceSize.y;

    return data;

}