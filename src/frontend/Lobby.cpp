#include "../../include/frontend/Lobby.h"

void Lobby::drawLobby(olc::PixelGameEngine *engine)
{
    rect borderTop = {{(engine->ScreenWidth() / 2.8f - engine->ScreenHeight() / 2), engine->ScreenHeight() / 10}, {engine->ScreenWidth() / 1.17f, engine->ScreenHeight() / 16}};
    rect borderBottom = {{(engine->ScreenWidth() / 2.8f - engine->ScreenHeight() / 2), engine->ScreenHeight() / 1.2f}, {engine->ScreenWidth() / 1.17f, engine->ScreenHeight() / 16}};
    rect borderTopLeft = {{(engine->ScreenWidth() / 2.8f - engine->ScreenHeight() / 2), engine->ScreenHeight() / 6.25f}, {engine->ScreenWidth() / 28, engine->ScreenHeight() / 4}};
    rect borderBottomLeft = {{(engine->ScreenWidth() / 2.8f - engine->ScreenHeight() / 2), engine->ScreenHeight() / 1.2f}, {engine->ScreenWidth() / 28, -engine->ScreenHeight() / 4}};
    rect borderTopRight = {{(engine->ScreenWidth() * 1.173f - engine->ScreenHeight() / 2), engine->ScreenHeight() / 6.25f}, {engine->ScreenWidth() / 28, engine->ScreenHeight() / 4}};
    rect borderBottomRight = {{(engine->ScreenWidth() * 1.173f - engine->ScreenHeight() / 2), engine->ScreenHeight() / 1.2f}, {engine->ScreenWidth() / 28, -engine->ScreenHeight() / 4}};
    rect borderLeftCorridorTop = {{0, engine->ScreenHeight() / 2.45f}, {engine->ScreenWidth() / 14.5, -engine->ScreenHeight() / 16}};
    rect borderLeftCorridorBottom = {{0, engine->ScreenHeight() / 1.55f}, {engine->ScreenWidth() / 14.5, -engine->ScreenHeight() / 16}};

    engine->DrawRect(borderTop.pos, borderTop.size, olc::WHITE);
    engine->DrawRect(borderBottom.pos, borderBottom.size, olc::WHITE);
    engine->DrawRect(borderTopLeft.pos, borderTopLeft.size, olc::WHITE);
    engine->DrawRect(borderBottomLeft.pos, borderBottomLeft.size, olc::WHITE);
    engine->DrawRect(borderTopRight.pos, borderTopRight.size, olc::WHITE);
    engine->DrawRect(borderBottomRight.pos, borderBottomRight.size, olc::WHITE);
    engine->DrawRect(borderLeftCorridorTop.pos, borderLeftCorridorTop.size, olc::WHITE);
    engine->DrawRect(borderLeftCorridorBottom.pos, borderLeftCorridorBottom.size, olc::WHITE);
}