#include "../../include/frontend/Lobby.h"

void Lobby::drawLobby(olc::PixelGameEngine* engine)
{
    rect r = { {(engine->ScreenWidth() / 2 - engine->ScreenHeight() / 2), engine->ScreenHeight() / 2 - 25.0f}, {6.0f, 50.0f} };
    rect borderTop = {{(engine->ScreenWidth() / 2.8f - engine->ScreenHeight() / 2), engine->ScreenHeight() / 10}, {engine->ScreenWidth() /1.17f, engine->ScreenHeight() / 16}};
    rect borderBottom = {{(engine->ScreenWidth() / 2.8f - engine->ScreenHeight() / 2), engine->ScreenHeight() / 1.2f}, {engine->ScreenWidth() /1.17f, engine->ScreenHeight() / 16}};
    rect borderTopLeft = {{(engine->ScreenWidth() / 2.8f - engine->ScreenHeight() / 2), engine->ScreenHeight() / 6.25f}, {engine->ScreenWidth() / 28, engine->ScreenHeight() / 4}};
    rect borderBottomLeft = {{(engine->ScreenWidth() / 2.8f - engine->ScreenHeight() / 2), engine->ScreenHeight() / 1.2f}, {engine->ScreenWidth() / 28, - engine->ScreenHeight() / 4}};
    rect borderTopRight = {{(engine->ScreenWidth() * 1.1763f - engine->ScreenHeight() / 2), engine->ScreenHeight() / 6.25f}, {engine->ScreenWidth() / 28, engine->ScreenHeight() / 4}};
    rect borderBottomRight = {{(engine->ScreenWidth() * 1.1763f - engine->ScreenHeight() / 2), engine->ScreenHeight() / 1.2f}, {engine->ScreenWidth() / 28, - engine->ScreenHeight() / 4}};
    
    engine->DrawRect(borderTop.pos,borderTop.size, olc::WHITE);
    engine->DrawRect(borderBottom.pos,borderBottom.size, olc::WHITE);
    engine->DrawRect(borderTopLeft.pos,borderTopLeft.size, olc::WHITE);
    engine->DrawRect(borderBottomLeft.pos,borderBottomLeft.size, olc::WHITE);
    engine->DrawRect(borderTopRight.pos,borderTopRight.size, olc::WHITE);
    engine->DrawRect(borderBottomRight.pos,borderBottomRight.size, olc::WHITE);
}