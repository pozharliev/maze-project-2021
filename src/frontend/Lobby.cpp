#include "../../include/frontend/Lobby.h"

void Lobby::drawLobby()
{
    rect r = { {(ScreenWidth() / 2 - ScreenHeight() / 2), ScreenHeight() / 2 - 25.0f}, {6.0f, 50.0f} };
    rect borderTop = {{(ScreenWidth() / 2.8f - ScreenHeight() / 2), ScreenHeight() / 10}, {ScreenWidth() /1.17f, ScreenHeight() / 16}};
    rect borderBottom = {{(ScreenWidth() / 2.8f - ScreenHeight() / 2), ScreenHeight() / 1.2f}, {ScreenWidth() /1.17f, ScreenHeight() / 16}};
    rect borderTopLeft = {{(ScreenWidth() / 2.8f - ScreenHeight() / 2), ScreenHeight() / 6.25f}, {ScreenWidth() / 28, ScreenHeight() / 4}};
    rect borderBottomLeft = {{(ScreenWidth() / 2.8f - ScreenHeight() / 2), ScreenHeight() / 1.2f}, {ScreenWidth() / 28, - ScreenHeight() / 4}};
    rect borderTopRight = {{(ScreenWidth() * 1.1763f - ScreenHeight() / 2), ScreenHeight() / 6.25f}, {ScreenWidth() / 28, ScreenHeight() / 4}};
    rect borderBottomRight = {{(ScreenWidth() * 1.1763f - ScreenHeight() / 2), ScreenHeight() / 1.2f}, {ScreenWidth() / 28, - ScreenHeight() / 4}};
    
    DrawRect(borderTop.pos,borderTop.size, olc::WHITE);
    DrawRect(borderBottom.pos,borderBottom.size, olc::WHITE);
    DrawRect(borderTopLeft.pos,borderTopLeft.size, olc::WHITE);
    DrawRect(borderBottomLeft.pos,borderBottomLeft.size, olc::WHITE);
    DrawRect(borderTopRight.pos,borderTopRight.size, olc::WHITE);
    DrawRect(borderBottomRight.pos,borderBottomRight.size, olc::WHITE);
}