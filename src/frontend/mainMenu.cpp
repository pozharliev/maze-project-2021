#include "../../include/frontend/mainMenu.h"

MainMenu::~MainMenu()
{
    delete welcomeLogo;
    delete welcomeLogoDecal;
}

bool MainMenu::pressAnyKey(olc::PixelGameEngine *engine)
{
    //Draw the logo of the game
    engine->DrawDecal({engine->ScreenWidth() / 6.2f, engine->ScreenHeight() / 5}, welcomeLogoDecal, {0.12f, 0.12f});
    engine->DrawString(engine->ScreenWidth() / 2 - 76, engine->ScreenHeight() / 1.2f, "Press X to continue", olc::WHITE, 1);
    //Listen for X key input
    if (engine->GetKey(olc::X).bPressed)
    {
        PlaySoundA("public/sfx/mainMenuEnterSFX.wav", NULL, SND_ASYNC);
        anyKeyPressed = true;
    }
    return true;
}

bool MainMenu::displayPauseMenu(olc::PixelGameEngine *engine, Collisions *collisions)
{
    std::string menuOptionsArr[2] = {"Continue", "Quit To Menu"};
    engine->Clear(olc::BLACK);
    int spacing = -16;

    for (int i = 0; i < 2; i++)
    {
        if (i == menuOption)
        {
            engine->DrawString(engine->ScreenWidth() / 2 - 56, engine->ScreenHeight() / 2 + spacing, "-> " + menuOptionsArr[i], olc::DARK_GREY);
        }
        else
        {
            engine->DrawString(engine->ScreenWidth() / 2 - 32, engine->ScreenHeight() / 2 + spacing, menuOptionsArr[i], olc::WHITE);
        }

        spacing += 32;
    }

    getMenuInput(engine, "pause", collisions);
    spacing = -16;
    return true;
}

bool MainMenu::displayMainMenu(olc::PixelGameEngine *engine, Collisions *collisions)
{
    std::string menuOptionsArr[3] = {"Start Game", "Options", "Quit Game"};
    engine->Clear(olc::BLACK);
    int spacing = -32;

    for (int i = 0; i < 3; i++)
    {
        if (i == menuOption)
        {
            engine->DrawString(engine->ScreenWidth() / 2 - 64, engine->ScreenHeight() / 2 + spacing, "-> " + menuOptionsArr[i], olc::DARK_GREY);
        }
        else
        {
            engine->DrawString(engine->ScreenWidth() / 2 - 40, engine->ScreenHeight() / 2 + spacing, menuOptionsArr[i], olc::WHITE);
        }

        spacing += 32;
    }
    getMenuInput(engine, "main", collisions);
    mainMenuEdit = true;
    spacing = -32;
    return true;
}

bool MainMenu::displayOptionsMenu(olc::PixelGameEngine *engine, Collisions *collisions)
{
    std::string menuOptionsArr[4] = {"Full Screen", "Sound", "Controls", "Back"};
    engine->Clear(olc::BLACK);
    int spacing = -32;

    for (int i = 0; i < 4; i++)
    {
        if (i == menuOption)
        {
            if (menuOptionsArr[i] == "Full Screen")
            {
                engine->DrawString(engine->ScreenWidth() / 2 - 64, engine->ScreenHeight() / 2 + spacing, "-> " + menuOptionsArr[i] + ": " + (fullScreen == true ? "on" : "off"), olc::DARK_GREY);
            }
            else if (menuOptionsArr[i] == "Sound")
            {
                engine->DrawString(engine->ScreenWidth() / 2 - 64, engine->ScreenHeight() / 2 + spacing, "-> " + menuOptionsArr[i] + ": " + (sound == true ? "on" : "off"), olc::DARK_GREY);
            }
            else
            {
                engine->DrawString(engine->ScreenWidth() / 2 - 64, engine->ScreenHeight() / 2 + spacing, "-> " + menuOptionsArr[i], olc::DARK_GREY);
            }
        }
        else if (menuOptionsArr[i] == "Full Screen")
        {
            engine->DrawString(engine->ScreenWidth() / 2 - 40, engine->ScreenHeight() / 2 + spacing, menuOptionsArr[i] + ": " + (fullScreen == true ? "on" : "off"), olc::WHITE);
        }
        else if (menuOptionsArr[i] == "Sound")
        {
            engine->DrawString(engine->ScreenWidth() / 2 - 40, engine->ScreenHeight() / 2 + spacing, menuOptionsArr[i] + ": " + (sound == true ? "on" : "off"), olc::WHITE);
        }
        else
        {
            engine->DrawString(engine->ScreenWidth() / 2 - 40, engine->ScreenHeight() / 2 + spacing, menuOptionsArr[i], olc::WHITE);
        }

        spacing += 32;
    }
    getMenuInput(engine, "options", collisions);
    optionsMenuEdit = true;
    spacing = -32;
    return true;
}

bool MainMenu::displayControllsMenu(olc::PixelGameEngine *engine, Collisions *collisions)
{
    engine->Clear(olc::BLACK);
    engine->DrawString(engine->ScreenWidth() / 2 - 112, engine->ScreenHeight() / 2 - 80, "Move Up           'UP ARROW'", olc::WHITE);
    engine->DrawString(engine->ScreenWidth() / 2 - 112, engine->ScreenHeight() / 2 - 55, "Move Down       'DOWN ARROW'", olc::WHITE);
    engine->DrawString(engine->ScreenWidth() / 2 - 112, engine->ScreenHeight() / 2 - 30, "Move Left       'LEFT ARROW'", olc::WHITE);
    engine->DrawString(engine->ScreenWidth() / 2 - 112, engine->ScreenHeight() / 2 - 5, "Move Right     'RIGHT ARROW'", olc::WHITE);
    engine->DrawString(engine->ScreenWidth() / 2 - 112, engine->ScreenHeight() / 2 + 20, "Dash                 'SHIFT'", olc::WHITE);
    engine->DrawString(engine->ScreenWidth() / 2 - 112, engine->ScreenHeight() / 2 + 45, "Reveal Path              'E'", olc::WHITE);
    engine->DrawString(engine->ScreenWidth() / 2 - 40, engine->ScreenHeight() / 1.1f, "-> Back", olc::DARK_GREY);
    getMenuInput(engine, "controlls", collisions);
    controllsEdit = true;
    return true;
}

bool MainMenu::displayLoseMenu(olc::PixelGameEngine *engine, Collisions *collisions)
{
    engine->Clear(olc::BLACK);
    engine->DrawString(engine->ScreenWidth() / 2 - 72.0f, engine->ScreenWidth() / 8, "You died!", olc::RED, 2);
    engine->DrawString(engine->ScreenWidth() / 2 - 55, engine->ScreenHeight() / 1.3f, "-> Quit game...", olc::DARK_GREY);
    getMenuInput(engine, "lose", collisions);
    return true;
}

bool MainMenu::displayWinMenu(olc::PixelGameEngine *engine, Collisions *collisions)
{
    engine->Clear(olc::BLACK);
    engine->DrawString(engine->ScreenWidth() / 2 - 72.0f, engine->ScreenWidth() / 8, "You...y.WHAT, YOU JUST WON THE GAME", olc::WHITE, 1);
    engine->DrawString(engine->ScreenWidth() / 2 - 55, engine->ScreenHeight() / 1.3f, "-> Quit game...", olc::DARK_GREY);
    getMenuInput(engine, "win", collisions);
    return true;
}

void MainMenu::getMenuInput(olc::PixelGameEngine *engine, std::string menuType, Collisions *collisions)
{
    if (menuType == "main")
    {
        optionsMenuEdit = false;

        if (engine->GetKey(olc::DOWN).bPressed)
        {
            if (sound)
            {
                PlaySoundA("public/sfx/mainMenuHoverSFX.wav", NULL, SND_ASYNC);
            }

            if (menuOption == 2)
            {
                menuOption = 0;
            }
            else
            {
                menuOption += 1;
            }
        }

        if (engine->GetKey(olc::UP).bPressed)
        {
            if (sound)
            {
                PlaySoundA("public/sfx/mainMenuHoverSFX.wav", NULL, SND_ASYNC);
            }
            if (menuOption == 0)
            {
                menuOption = 2;
            }
            else
            {
                menuOption -= 1;
            }
        }

        if (engine->GetKey(olc::ENTER).bPressed)
        {
            if (sound)
            {
                PlaySoundA("public/sfx/mainMenuSelectSFX.wav", NULL, SND_ASYNC);
            }
            if (menuOption == 0 && mainMenuEdit)
            {
                mainMenuEnabled = false;
                gameStarted = true;
                menuOption = 0; // reset the selected option after quitting the menu
            }
            if (menuOption == 1)
            {
                menuOption = 0;
                optionsMenuEnabled = true;
                mainMenuEnabled = false;
            }
            if (menuOption == 2)
            {
                isExit = true;
            }
        }
    }

    if (menuType == "options")
    {
        controllsEdit = false;

        if (engine->GetKey(olc::DOWN).bPressed)
        {
            if (sound)
            {
                PlaySoundA("public/sfx/mainMenuHoverSFX.wav", NULL, SND_ASYNC);
            }
            if (menuOption == 3)
            {
                menuOption = 0;
            }
            else
            {
                menuOption += 1;
            }
        }

        if (engine->GetKey(olc::UP).bPressed)
        {
            if (sound)
            {
                PlaySoundA("public/sfx/mainMenuHoverSFX.wav", NULL, SND_ASYNC);
            }
            if (menuOption == 0)
            {
                menuOption = 3;
            }
            else
            {
                menuOption -= 1;
            }
        }

        if (engine->GetKey(olc::ENTER).bPressed && optionsMenuEdit)
        {
            if (sound)
            {
                PlaySoundA("public/sfx/mainMenuSelectSFX.wav", NULL, SND_ASYNC);
            }
            if (menuOption == 0)
            {
                if (fullScreen == false)
                {
                    saveFile.open("data/saveFile.save", std::ofstream::out | std::ofstream::trunc);
                    saveFile << "true";
                    saveFile.close();
                    fullScreen = true;
                    isExit = true;
                }
                else
                {
                    saveFile.open("data/saveFile.save", std::ofstream::out | std::ofstream::trunc);
                    saveFile << "false";
                    saveFile.close();
                    fullScreen = false;
                    isExit = true;
                }
            }

            if (menuOption == 1)
            {
                sound = !sound;
            }

            if (menuOption == 2)
            {
                controllsMenuEnabled = true;
                optionsMenuEnabled = false;
            }

            if (menuOption == 3)
            {
                optionsMenuEnabled = false;
                mainMenuEnabled = true;
                menuOption = 0;
            }
        }
    }

    if (menuType == "pause")
    {
        mainMenuEdit = false;

        if (engine->GetKey(olc::DOWN).bPressed)
        {
            if (sound)
            {
                PlaySoundA("public/sfx/mainMenuHoverSFX.wav", NULL, SND_ASYNC);
            }
            if (menuOption == 1)
            {
                menuOption = 0;
            }
            else if (menuOption == 0)
            {
                menuOption = 1;
            }
        }

        if (engine->GetKey(olc::UP).bPressed)
        {
            if (sound)
            {
                PlaySoundA("public/sfx/mainMenuHoverSFX.wav", NULL, SND_ASYNC);
            }
            if (menuOption == 0)
            {
                menuOption = 1;
            }
            else if (menuOption == 1)
            {
                menuOption = 0;
            }
        }

        if (engine->GetKey(olc::ENTER).bPressed)
        {
            if (sound)
            {
                PlaySoundA("public/sfx/mainMenuSelectSFX.wav", NULL, SND_ASYNC);
            }
            if (menuOption == 0)
            {
                pauseMenuEnabled = false;
                mainMenuEnabled = true;
                menuOption = 0; // reset the selected option after quitting the menu
            }
            if (menuOption == 1)
            {
                mainMenuEnabled = true;
                pauseMenuEnabled = false;
                menuOption = 0;
            }
        }
    }

    if (menuType == "controlls")
    {

        if (engine->GetKey(olc::ENTER).bPressed && controllsEdit)
        {
            if (sound)
            {
                PlaySoundA("public/sfx/mainMenuSelectSFX.wav", NULL, SND_ASYNC);
            }
            controllsMenuEnabled = false;
            optionsMenuEnabled = true;
            menuOption = 0;
        }
    }

    if (menuType == "lose")
    {
        mainMenuEdit = false;

        if (engine->GetKey(olc::ENTER).bPressed)
        {
            if (sound)
            {
                PlaySoundA("public/sfx/mainMenuSelectSFX.wav", NULL, SND_ASYNC);
            }
            isExit = true;
        }
    }

    if (menuType == "win")
    {
        if (engine->GetKey(olc::ENTER).bPressed)
        {
            if (sound)
            {
                PlaySoundA("public/sfx/mainMenuSelectSFX.wav", NULL, SND_ASYNC);
            }
            isExit = true;
        }
    }
}