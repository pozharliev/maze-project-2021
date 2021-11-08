#define OLC_PGE_APPLICATION
#define OLC_PGEX_ANIMSPR
#include "include/backend/gameManager.h"

#include <iostream>

//GO BIG OR GO HOME

int main()
{
    olc::PixelGameEngine engine;
    GameManager *gameManager = new GameManager;

    gameManager->mainMenu->saveFile.open("data/saveFile.save");
    if (gameManager->mainMenu->saveFile.is_open())
    {
        while (getline(gameManager->mainMenu->saveFile, gameManager->mainMenu->line))
        {
            if (gameManager->mainMenu->line == "true")
            {
                gameManager->mainMenu->fullScreen = true;
            }
            else
            {
                gameManager->mainMenu->fullScreen = false;
            }
        }
        gameManager->mainMenu->saveFile.close();
    }

    if (gameManager->Construct(engine.ScreenWidth() * 1.5f - 46, engine.ScreenHeight() - 46, 5, 5, gameManager->mainMenu->fullScreen))
    {
        auto rc = gameManager->Start();
    }

    delete gameManager;
}