#include "../../include/backend/gameManager.h"

GameManager::GameManager()
{
  mainMenu = new MainMenu;
  player = new Player;
  floorCount = 2;
  collisions = new Collisions;
}

GameManager::~GameManager()
{
  for(auto i : floors)
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
    mainMenu->welcomeLogo = new olc::Sprite("public/VAVYLON_LOGO_BIG_NOBG.png");
    mainMenu->welcomeLogoDecal = new olc::Decal(mainMenu->welcomeLogo);

    for(int i = 0; i < floorCount; i++)
    {
      floors.push_back(new Lobby(i));
      floors.at(i)->inMaze = false;
      floors.at(i)->lobbyRoom = new olc::Sprite("public/lobby.png");
      floors.at(i)->lobbyForegroundSprite = new olc::Sprite("public/foreGroundLobby.png");
      floors.at(i)->lobbyForeground = new olc::Decal(floors.at(i)->lobbyForegroundSprite);
      // floors.at(i)->room->path = false;
    }
    currentFloor = 0;

    collisions->colliding = false;
    collisions->gameEnded = false;

    return true;
}

bool GameManager::OnUserUpdate(float fElapsedTime)
{
    Clear(olc::BLACK);

    if (mainMenu->gameStarted)
    {
      if(!inCutscene)
      {
        Game(fElapsedTime);
      }
      else
      {
        Cutscene(fElapsedTime);
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
      if(!floors.at(currentFloor)->inMaze)
      {
        floors.at(currentFloor)->drawLobbyForeground(this);
      }
      player->drawPlayerVignette(this);
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
    if(this->GetKey(olc::G).bPressed)
    {
      if(currentFloor == floorCount-1)
      {
        //https://www.youtube.com/watch?v=fmN09mVQ3YE
        exit(0);
      }
      else
      {
        currentFloor++;
      }
    }

    // if(this->GetKey(olc::E).bPressed /*&& player->playerInv.pathScroll*/)
    // {
    //   floors.at(currentFloor)->room->path = !floors.at(currentFloor)->room->path;
    // }

    //If the input is left arrow
    if (this->GetKey(olc::LEFT).bHeld && mainMenu->pauseMenuEnabled == false && mainMenu->mainMenuEnabled == false && collisions->lastCollisionDir != player->PLAYER_DIRS::LEFT)
    {
      player->movePlayer(this, olc::LEFT, elapsedTime);

      if(this->GetKey(olc::SHIFT).bPressed && player->playerInv.dashScroll == true)
      {
        PlaySoundA("public/sfx/dashSFX.wav", NULL, SND_ASYNC);
        player->dashing = true;
        player->playerX -= 17.0f;
        player->Animator->SetState("dashLeft");
      }
      if(this->GetKey(olc::SHIFT).bReleased && player->playerInv.dashScroll == true)
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

      if(this->GetKey(olc::SHIFT).bPressed && player->playerInv.dashScroll == true)
      {
        PlaySoundA("public/sfx/dashSFX.wav", NULL, SND_ASYNC);
        player->dashing = true;
        player->playerX += 17.0f;
        player->Animator->SetState("dashRight");
      }
      if(this->GetKey(olc::SHIFT).bReleased && player->playerInv.dashScroll == true)
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

      if(this->GetKey(olc::SHIFT).bPressed && player->playerInv.dashScroll == true)
      {
        PlaySoundA("public/sfx/dashSFX.wav", NULL, SND_ASYNC);
        player->dashing = true;
        player->playerY -= 17.0f;
        player->Animator->SetState("dashUp");
      }

      if(this->GetKey(olc::SHIFT).bReleased && player->playerInv.dashScroll == true)
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

      if(this->GetKey(olc::SHIFT).bPressed && player->playerInv.dashScroll == true)
      {
        PlaySoundA("public/sfx/dashSFX.wav", NULL, SND_ASYNC);
        player->dashing = true;
        player->playerY += 17.0f;
        player->Animator->SetState("dashDown");
      }

      if(this->GetKey(olc::SHIFT).bReleased && player->playerInv.dashScroll == true)
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