#define OLC_PGE_APPLICATION
#include "libs/olcPixelGameEngine.h"
#include "include/frontend/mainMenu.h"
#include "include/frontend/Lobby.h"
#include "include/frontend/Player.h"
// #include "include/frontend/GameManager.h"
#include <iostream>

class GameManager : public olc::PixelGameEngine{

  public:
    MainMenu* mainMenu;
    Player* player;
    Lobby* lobby;
    bool fullScreen;
    std::fstream saveFile;
    std::string line;

  public:
    GameManager()
    {
        mainMenu = new MainMenu;
        player = new Player;
        lobby = new Lobby;
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

};


//GO BIG OR GO HOME

int main()
{
  olc::PixelGameEngine engine;
	GameManager gameManager;

	// game.saveFile.open("docs/saveFile.save");
  //   if (game.saveFile.is_open())
  //         {
  //           while ( getline (game.saveFile, game.line) )
  //           {
  //             if(game.line == "true"){
  //               game.fullScreen = true;
  //             }
  //             else{
  //               game.fullScreen = false;
  //             }
  //           }
  //           game.saveFile.close();
  //         }

	if (gameManager.Construct(engine.ScreenWidth() * 1.5f - 46, engine.ScreenHeight() - 46, 5, 5))
		gameManager.Start();
}