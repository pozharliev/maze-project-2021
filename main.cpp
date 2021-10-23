#include "include/frontend/game.h"
#include <iostream>

//GO BIG OR GO HOME

int main()
{
	olc::PixelGameEngine engine;
	Game game;

	game.readFile.open("data/saveFile.save");
    if (game.readFile.is_open())
          {
            while ( getline (game.readFile, game.line) )
            {
              if(game.line == "true"){
                game.fullScreen = true;
              }
              else{
                game.fullScreen = false;
              }
            }
            game.readFile.close();
          }
    std::cout << game.fullScreen;

	if (game.Construct(engine.ScreenWidth() * 1.5f - 46, engine.ScreenHeight() - 46, 5, 5, game.fullScreen))
		game.Start();
}