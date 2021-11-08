#include "../../include/frontend/lobby.h"

Lobby::Lobby(int count)
{
    thisLobbyCount = count;
    room = new Room(24, 12);
    room->runeSprite = new olc::Sprite("public/rune.png");
    room->rune = new olc::Decal(room->runeSprite);
    room->runeSpriteIcon = new olc::Sprite("public/runeIcon.png");
    room->runeIcon = new olc::Decal(room->runeSpriteIcon);
    room->scrollDashSprite = new olc::Sprite("public/scrollDash.png");
    room->scrollDash = new olc::Decal(room->scrollDashSprite);
    room->runeTileSprite = new olc::Sprite("public/rune_tile.png");
    room->scroll = new olc::Sprite("public/scroll.png");
    room->scrollDecal = new olc::Decal(room->scroll);
    room->roomEnriched = false;
    room->setUpScrollAnimations();
}

Lobby::~Lobby()
{
    delete lobbyRoom;
    delete lobbyForeground;
}

void Lobby::initLobby()
{
    lobbyWidth = 32;
    lobbyHeight = 17;

    lobbyRawData += ".............######.............";
    lobbyRawData += ".............#....#.............";
    lobbyRawData += "....##########....##########....";
    lobbyRawData += "....#......................#....";
    lobbyRawData += "....#......................#....";
    lobbyRawData += "....#......................#....";
    lobbyRawData += "#####......................#####";
    lobbyRawData += "................................";
    lobbyRawData += "................................";
    lobbyRawData += "................................";
    lobbyRawData += "................................";
    lobbyRawData += "................................";
    lobbyRawData += "#####......................#####";
    lobbyRawData += "....#......................#....";
    lobbyRawData += "....#......................#....";
    lobbyRawData += "....#......................#....";
    lobbyRawData += "....########################....";

    tileWidth = 11;
    tileHeight = 11;

    leftMazeEnter = false;
    rightMazeEnter = false;
    inLeftMaze = false;
    inRightMaze = false;
}

//Draw the hall collision

bool Lobby::hallCollision(Player *player, rect roomLeft)
{
    return pointCollRect(player->playerPos, roomLeft);
}

bool Lobby::pointCollRect(const olc::vf2d &p, const rect &r)
{
    return (p.x >= r.pos.x && p.y >= r.pos.y && p.x < r.pos.x + r.size.x && p.y < r.pos.y + r.size.y);
}

char Lobby::getTile(int x, int y)
{
    if (x >= 0 && x < lobbyWidth && y >= 0 && y < lobbyWidth)
        return lobbyRawData[y * lobbyWidth + x];
}

void Lobby::drawLobby(olc::PixelGameEngine *engine, Player *player)
{

    if (inMaze)
    {
        if (inLeftMaze)
        {
            room->DrawRoom(engine, "left");
            currentMaze = LEFT;
            if (!leftMazeEnter)
            {
                player->playerX = 320.0f;
                leftMazeEnter = true;
            }
        }
        if (inRightMaze)
        {
            room->DrawRoom(engine, "right");
            currentMaze = RIGHT;
            if (!rightMazeEnter)
            {
                player->playerX = abs(player->playerX - engine->ScreenWidth() + 15.0f);
                rightMazeEnter = true;
            }
        }
    }
    else
    {
        initLobby();
        visibleTilesX = engine->ScreenWidth() / tileWidth;
        visibleTilesY = engine->ScreenHeight() / tileHeight;

        rect roomLeft = {{-10.0f, engine->ScreenHeight() / 2.5f}, {10.0f, 43.0f}};

        rect roomRight = {{engine->ScreenWidth() - 1.0f, engine->ScreenHeight() / 2.5f}, {10.0f, 43.0f}};

        stairCase = {{engine->ScreenWidth() / 2.30f, 5.0f}, {43.0f, 10.0f}};

        engine->DrawSprite(0, 0, lobbyRoom);

        if (hallCollision(player, roomLeft))
        {
            inMaze = true;
            inLeftMaze = true;
        }

        if (hallCollision(player, roomRight))
        {
            inMaze = true;
            inRightMaze = true;
        }
    }
}

void Lobby::drawLobbyForeground(olc::PixelGameEngine *engine)
{
    engine->DrawDecal({0, 0}, lobbyForeground);
    engine->DrawDecal({engine->ScreenWidth() / 2 - 25, 0}, lobbyRaysDecal);
}