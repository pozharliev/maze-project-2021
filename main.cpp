#define OLC_PGE_APPLICATION
#include "libs/olcPixelGameEngine.h"
#include "include/frontend/mainMenu.h"
#include "include/frontend/Lobby.h"
#include "include/frontend/room.h"
#include "include/frontend/Player.h"
// #include "include/frontend/GameManager.h"
#include <iostream>

class GameManager : public olc::PixelGameEngine{

  private:
    bool generatedMaze = false;


  public:
    MainMenu* mainMenu;
    Player* player;
    Lobby* lobby;
    Room* room;

  public:
    GameManager()
    {
      mainMenu = new MainMenu;
      player = new Player;
      lobby = new Lobby;
      room = new Room(14, 14);
    }

  private:
    bool OnUserCreate() override
    {
      player->playerX = ScreenWidth() / 2;
      player->playerY = ScreenHeight() / 2;
      player->playerRadius = 5.0f;

      mainMenu->mainMenuEnabled = true;
      mainMenu->pauseMenuEnabled = false;
      mainMenu->optionsMenuEnabled = false;
      mainMenu->menuOption = 0;
      mainMenu->gameStarted = false;

      return true;
    }

    bool OnUserUpdate(float fElapsedTime) override
    {

      Clear(olc::BLACK);

      if(mainMenu->gameStarted)
      {
        startGame(fElapsedTime);
      }

      if(mainMenu->mainMenuEnabled){
        mainMenu->displayMainMenu(this);
      }

      if(mainMenu->pauseMenuEnabled){
        mainMenu->displayPauseMenu(this);
      }
      
      if(mainMenu->optionsMenuEnabled && mainMenu->mainMenuEnabled == false){
        mainMenu->displayOptionsMenu(this);
      }
    
      return true;
    }

    bool startGame(float fElapsedTime)
    {
      getInput(fElapsedTime);

      player->playerPos = {player->playerX, player->playerY};

      player->drawPlayer(this);

      //If go into hall generate Room
      if(!generatedMaze)
      {
        room->generateRoom();
      }
      generatedMaze = true;

    }

    void getInput(float elapsedTime)
    {
      if(this->GetKey(olc::LEFT).bHeld && player->playerX >= (this->ScreenWidth() / 2 - this->ScreenHeight() / 2) + 0.5f + 0.4f && mainMenu->pauseMenuEnabled == false && mainMenu->mainMenuEnabled == false){
        player->movePlayer(this, olc::LEFT, elapsedTime);
      }

      if(this->GetKey(olc::LEFT).bReleased){
          player->playerSpeed = PLAYER_SPEED;
      }

      if(this->GetKey(olc::RIGHT).bHeld  && player->playerX <= this->ScreenWidth() && mainMenu->pauseMenuEnabled == false && mainMenu->mainMenuEnabled == false){
        player->movePlayer(this, olc::RIGHT, elapsedTime);
      }
      if(GetKey(olc::RIGHT).bReleased){
        player->playerSpeed = PLAYER_SPEED;
      }

      if(this->GetKey(olc::UP).bHeld && player->playerY >= 0 && mainMenu->pauseMenuEnabled == false && mainMenu->mainMenuEnabled == false){
        player->movePlayer(this, olc::UP, elapsedTime);
      }
      if(GetKey(olc::UP).bReleased){
        player->playerSpeed = PLAYER_SPEED;
      }

      if(GetKey(olc::DOWN).bHeld && player->playerY <= ScreenHeight() && mainMenu->pauseMenuEnabled == false && mainMenu->mainMenuEnabled == false){
        player->movePlayer(this, olc::DOWN, elapsedTime);
      }
      if(GetKey(olc::DOWN).bReleased){
        player->playerSpeed = PLAYER_SPEED;
      }

      if(GetKey(olc::ESCAPE).bPressed && !mainMenu->mainMenuEnabled && !mainMenu->optionsMenuEnabled){
        if(!mainMenu->pauseMenuEnabled){
          mainMenu->pauseMenuEnabled = true;
        }
        else{
          mainMenu->pauseMenuEnabled = false;
        }
      }

      if(this->GetKey(olc::F4).bPressed){
        exit(0);
      }
    }



};


//GO BIG OR GO HOME

int main()
{
  olc::PixelGameEngine engine;
	GameManager gameManager;

	gameManager.mainMenu->saveFile.open("data/saveFile.save");
    if (gameManager.mainMenu->saveFile.is_open())
    {
      while ( getline (gameManager.mainMenu->saveFile, gameManager.mainMenu->line) )
      {
        if(gameManager.mainMenu->line == "true"){
          gameManager.mainMenu->fullScreen = true;
        }
        else{
          gameManager.mainMenu->fullScreen = false;
        }
      }
      gameManager.mainMenu->saveFile.close();
    }

	if (gameManager.Construct(engine.ScreenWidth() * 1.5f - 46, engine.ScreenHeight() - 46, 5, 5, gameManager.mainMenu->fullScreen))
		gameManager.Start();
}