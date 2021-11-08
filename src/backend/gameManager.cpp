#include "../../include/backend/gameManager.h"

GameManager::GameManager()
{
    mainMenu = new MainMenu;
    player = new Player;
    floorCount = 3;
    collisions = new Collisions;
}

GameManager::~GameManager()
{
    for (auto i : floors)
    {
        delete i;
    }
    delete cutsceneSprite;
    delete cutscene;

    delete collisions;
    delete player;
    delete mainMenu;
}

bool GameManager::OnUserCreate()
{
    cutsceneSprite = new olc::Sprite("public/Cutscene.png");
    cutscene = new olc::Decal(cutsceneSprite);
    inCutscene = false;
    vignette = true;

    player->innitPlayer();
    player->playerX = ScreenWidth() / 2;
    player->playerY = ScreenHeight() / 2;
    player->playerRadius = 5.0f;
    player->playerPos = {player->playerX, player->playerY};
    player->playerSpeed = 50.0f;
    player->playerVelX = 0.0f;
    player->playerVelY = 0.0f;

    mainMenu->isExit = false;
    mainMenu->mainMenuEnabled = true;
    mainMenu->pauseMenuEnabled = false;
    mainMenu->optionsMenuEnabled = false;
    mainMenu->controllsMenuEnabled = false;
    mainMenu->menuOption = 0;
    mainMenu->gameStarted = false;
    mainMenu->anyKeyPressed = false;
    mainMenu->sound = true;
    mainMenu->welcomeLogo = new olc::Sprite("public/VAVYLON_LOGO_BIG_NOBG.png");
    mainMenu->welcomeLogoDecal = new olc::Decal(mainMenu->welcomeLogo);

    for (int i = 0; i < floorCount; i++)
    {
        floors.push_back(new Lobby(i));
        floors.at(i)->inMaze = false;
        floors.at(i)->lobbyRoom = new olc::Sprite("public/lobby.png");
        floors.at(i)->lobbyForegroundSprite = new olc::Sprite("public/foreGroundLobby.png");
        floors.at(i)->lobbyForeground = new olc::Decal(floors.at(i)->lobbyForegroundSprite);
        floors.at(i)->room->leftRunePickedUp = false;
        floors.at(i)->room->rightRunePickedUp = false;
        floors.at(i)->lobbyRays = new olc::Sprite("public/rays.png");
        floors.at(i)->lobbyRaysDecal = new olc::Decal(floors.at(i)->lobbyRays);
        floors.at(i)->room->pathEnabled = false;
    }
    currentFloor = 0;

    collisions->colliding = false;
    collisions->gameEnded = false;

    return true;
}

bool GameManager::OnUserUpdate(float fElapsedTime)
{
    floors.at(currentFloor)->room->sound = mainMenu->sound;
    Clear(olc::BLACK);

    if (mainMenu->gameStarted)
    {
        if (!inCutscene)
        {
            Game(fElapsedTime);
        }
        else
        {
            Cutscene(fElapsedTime);
        }
    }

    if (!floors.at(currentFloor)->inMaze)
    {
        if (floors.at(currentFloor)->hallCollision(player, floors.at(currentFloor)->stairCase))
        {
            if (player->playerInv.runes == 2)
            {
                player->playerInv.runes = 0;
                if (currentFloor == floorCount - 1)
                {
                    //Сомтаймс уин, сомтаймс лонт
                    exit(0);
                }
                else
                {
                    currentFloor++;
                    player->playerX = this->ScreenWidth() / 2;
                    player->playerY = this->ScreenHeight() - 30.0f;
                }
            }
        }
    }

    if (mainMenu->anyKeyPressed)
    {
        if (mainMenu->mainMenuEnabled)
        {
            mainMenu->displayMainMenu(this, collisions);
        }

        if (mainMenu->pauseMenuEnabled)
        {
            mainMenu->displayPauseMenu(this, collisions);
        }

        if (mainMenu->optionsMenuEnabled && !mainMenu->mainMenuEnabled)
        {
            mainMenu->displayOptionsMenu(this, collisions);
        }

        if (mainMenu->controllsMenuEnabled)
        {
            mainMenu->displayControllsMenu(this, collisions);
        }

        if (collisions->gameEnded && !mainMenu->pauseMenuEnabled)
        {
            mainMenu->displayLoseMenu(this, collisions);
        }
    }
    else
    {
        mainMenu->pressAnyKey(this);
    }

    return !mainMenu->isExit;
}

void GameManager::Game(float fElapsedTime)
{
    getInput(fElapsedTime);

    if (!mainMenu->pauseMenuEnabled && !mainMenu->mainMenuEnabled && !mainMenu->optionsMenuEnabled && !mainMenu->controllsMenuEnabled && !collisions->gameEnded)
    {
        floors.at(currentFloor)->drawLobby(this, player);

        if (!player->firstPlayerMove)
        {
            collisions->checkCollisions(this, player, floors.at(currentFloor), floors.at(currentFloor)->room);
        }

        player->playerPos = {player->playerX, player->playerY};
        player->drawPlayer(this, fElapsedTime);
        if (!floors.at(currentFloor)->inMaze)
        {
            floors.at(currentFloor)->drawLobbyForeground(this);
        }
        if (vignette)
        {
            player->drawPlayerVignette(this);
        }
        this->DrawDecal({this->ScreenWidth() - 28, 4.5f}, floors.at(currentFloor)->room->runeIcon, {0.44f, 0.44f});
        this->DrawString(this->ScreenWidth() - 14, 5, std::to_string(player->playerInv.runes), olc::WHITE, 1);
        if (player->playerInv.dashScroll == true)
        {
            this->DrawDecal({5, 4.5f}, floors.at(currentFloor)->room->scrollDash, {0.22, 0.22});
        }
        if (player->playerInv.pathScroll == true)
        {
            this->DrawDecal({5, 11.5f}, floors.at(currentFloor)->room->scrollDecal, {0.22, 0.22});
        }
        if (player->playerInv.speedScroll == true)
        {
            this->DrawDecal({5, 16.5f}, floors.at(currentFloor)->room->scrollDecal, {0.22, 0.22});
        }
    }
}

void GameManager::Cutscene(float fElapsedTime)
{
    getInput(fElapsedTime);

    if (!mainMenu->pauseMenuEnabled && !mainMenu->mainMenuEnabled && !mainMenu->optionsMenuEnabled)
    {
        DrawDecal({0.0f - player->playerX, 0.0f - player->playerY}, cutscene);
        player->playerPos = {player->playerX, player->playerY};
        player->playerSpeed = 30.0f;
        // if (!player->firstPlayerMove)
        // {
        //   collisions->checkCollisions(player, lobby, room);
        // }
        player->drawPlayer(this, fElapsedTime);
    }
}

void GameManager::getInput(float elapsedTime)
{
    //Left here for debugging purposes
    if (this->GetKey(olc::G).bPressed)
    {
        if (currentFloor == floorCount - 1)
        {
            mainMenu->isExit = true;
        }
        else
        {
            currentFloor++;
        }
    }

    if (this->GetKey(olc::Q).bPressed)
    {
        vignette = !vignette;
    }

     if(this->GetKey(olc::E).bPressed /*&& player->playerInv.pathScroll*/)
     {
       floors.at(currentFloor)->room->pathEnabled = !floors.at(currentFloor)->room->pathEnabled;
     }

    //If the input is left arrow
    if (this->GetKey(olc::LEFT).bHeld && mainMenu->pauseMenuEnabled == false && mainMenu->mainMenuEnabled == false && collisions->lastCollisionDir != player->PLAYER_DIRS::LEFT)
    {
        player->movePlayer(this, olc::LEFT, elapsedTime);

        if (this->GetKey(olc::SHIFT).bPressed && player->playerInv.dashScroll == true)
        {
            if (mainMenu->sound)
            {
                PlaySoundA("public/sfx/dashSFX.wav", NULL, SND_ASYNC);
            }
            player->dashing = true;
            player->playerX -= 20.0f;
            player->Animator->SetState("dashLeft");
        }
        if (this->GetKey(olc::SHIFT).bReleased && player->playerInv.dashScroll == true)
        {
            player->dashing = false;
        }
    }

    if (this->GetKey(olc::LEFT).bReleased)
    {
        player->playerSpeed = 60;
        player->Animator->SetState("leftIdle");
    }

    //If the input is right arrow
    if (this->GetKey(olc::RIGHT).bHeld && mainMenu->pauseMenuEnabled == false && mainMenu->mainMenuEnabled == false && collisions->lastCollisionDir != player->PLAYER_DIRS::RIGHT)
    {
        player->movePlayer(this, olc::RIGHT, elapsedTime);

        if (this->GetKey(olc::SHIFT).bPressed && player->playerInv.dashScroll == true)
        {
            if (mainMenu->sound)
            {
                PlaySoundA("public/sfx/dashSFX.wav", NULL, SND_ASYNC);
            }
            player->dashing = true;
            player->playerX += 20.0f;
            player->Animator->SetState("dashRight");
        }
        if (this->GetKey(olc::SHIFT).bReleased && player->playerInv.dashScroll == true)
        {
            player->dashing = false;
        }
    }

    if (GetKey(olc::RIGHT).bReleased)
    {
        player->playerSpeed = 60;
        player->Animator->SetState("rightIdle");
    }

    //If the input is up arrow
    if (this->GetKey(olc::UP).bHeld && mainMenu->pauseMenuEnabled == false && mainMenu->mainMenuEnabled == false && collisions->lastCollisionDir != player->PLAYER_DIRS::UP)
    {
        player->movePlayer(this, olc::UP, elapsedTime);

        if (this->GetKey(olc::SHIFT).bPressed && player->playerInv.dashScroll == true)
        {
            if (mainMenu->sound)
            {
                PlaySoundA("public/sfx/dashSFX.wav", NULL, SND_ASYNC);
            }
            player->dashing = true;
            player->playerY -= 20.0f;
            player->Animator->SetState("dashUp");
        }

        if (this->GetKey(olc::SHIFT).bReleased && player->playerInv.dashScroll == true)
        {
            player->dashing = false;
        }
    }

    if (GetKey(olc::UP).bReleased)
    {
        player->playerSpeed = 60;
        player->Animator->SetState("upIdle");
    }

    //If the input is down arrow
    if (GetKey(olc::DOWN).bHeld && mainMenu->pauseMenuEnabled == false && mainMenu->mainMenuEnabled == false && collisions->lastCollisionDir != player->PLAYER_DIRS::DOWN)
    {
        player->movePlayer(this, olc::DOWN, elapsedTime);

        if (this->GetKey(olc::SHIFT).bPressed && player->playerInv.dashScroll == true)
        {
            if (mainMenu->sound)
            {
                PlaySoundA("public/sfx/dashSFX.wav", NULL, SND_ASYNC);
            }
            player->dashing = true;
            player->playerY += 20.0f;
            player->Animator->SetState("dashDown");
        }

        if (this->GetKey(olc::SHIFT).bReleased && player->playerInv.dashScroll == true)
        {
            player->dashing = false;
        }
    }

    if (GetKey(olc::DOWN).bReleased)
    {
        player->playerSpeed = 60;
        player->Animator->SetState("downIdle");
    }

    if (GetKey(olc::ESCAPE).bPressed && !mainMenu->mainMenuEnabled && !mainMenu->optionsMenuEnabled && !collisions->gameEnded)
    {
        if (!mainMenu->pauseMenuEnabled)
        {
            mainMenu->pauseMenuEnabled = true;
        }
        else
        {
            mainMenu->pauseMenuEnabled = false;
        }
    }
}