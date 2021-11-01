#include "../../include/frontend/playerAnimator.h"

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