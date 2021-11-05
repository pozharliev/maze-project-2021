#pragma once

#include "../backend/libs.h"

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
        cs_context_t* soundContext;
        cs_loaded_sound_t menuHoverLoad;
        cs_playing_sound_t menuHoverSFX;

    public:
        ~MainMenu();

        bool displayPauseMenu(olc::PixelGameEngine* engine);

        bool displayMainMenu(olc::PixelGameEngine* engine);

        bool displayOptionsMenu(olc::PixelGameEngine* engine);

        void getMenuInput(olc::PixelGameEngine* engine, std::string menuType);

        bool pressAnyKey(olc::PixelGameEngine* engine);
};