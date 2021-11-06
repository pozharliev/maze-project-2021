#pragma once

#include "../backend/libs.h"
#include "../backend/collisions.h"

class MainMenu
{
    public:
        bool fullScreen;
        std::fstream saveFile;
        std::string line;

    public:
        bool pauseMenuEnabled;
        bool mainMenuEnabled;
        bool optionsMenuEnabled;
        int menuOption;
        bool optionsMenuEdit;
        bool mainMenuEdit;
        bool gameStarted;
        bool anyKeyPressed;
        olc::Sprite* welcomeLogo;
        olc::Decal* welcomeLogoDecal;

    public:
        ~MainMenu();

        bool displayPauseMenu(olc::PixelGameEngine* engine, Collisions* collisions);

        bool displayMainMenu(olc::PixelGameEngine* engine, Collisions* collisions);

        bool displayOptionsMenu(olc::PixelGameEngine* engine, Collisions* collisions);

        bool displayLoseMenu(olc::PixelGameEngine *engine, Collisions* collisions);

        void getMenuInput(olc::PixelGameEngine* engine, std::string menuType, Collisions* collisions);

        bool pressAnyKey(olc::PixelGameEngine* engine);
};