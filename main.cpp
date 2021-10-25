#define OLC_PGE_APPLICATION
#include "libs/olcPixelGameEngine.h"
#include "include/frontend/Lobby.h"
#include "include/frontend/Player.h"
// #include "include/frontend/GameManager.h"
#include <iostream>

class GameManager : public olc::PixelGameEngine{

  public:
    Player* player;
    Lobby* lobby;

  public:
    GameManager()
    {
        player = new Player;
        lobby = new Lobby;
    }

  private:
    bool OnUserCreate()
    {
      player->playerX = ScreenWidth() / 2;
      player->playerY = ScreenHeight() / 2;
      player->playerRadius = 5.0f;

      return true;
    }

    bool OnUserUpdate(float fElapsedTime)
    {
      player->drawPlayer(this);
      //DrawCircle(player->playerX, player->playerY, player->playerRadius, olc::RED);

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