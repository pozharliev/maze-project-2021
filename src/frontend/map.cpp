#define OLC_PGE_APPLICATION
#define OLC_PGEX_TRANSFORMEDVIEW
#include "../../include/frontend/map.h"

Map::Map(){
    initMap(1);
}

bool Map::OnUserCreate()
{
    border = {{84, 0}, {ScreenWidth() - 169.0f, ScreenHeight() - 1.0f}};
    return true;
}

bool Map::OnUserUpdate(float fElapsedTime)
{
    initMap(1);
    return true;
}

void Map::initMap(int level)
{
    drawBorder();
}

void Map::drawBorder()
{
    DrawRect(border.pos,border.size, olc::WHITE);
}