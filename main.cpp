#include "include/frontend/game.h"
#include <iostream>

//GO BIG OR GO HOME

int main()
{
	olc::PixelGameEngine engine;
	Game game;

	game.saveFile.open("docs/saveFile.save");
    if (game.saveFile.is_open())
          {
            while ( getline (game.saveFile, game.line) )
            {
              if(game.line == "true"){
                game.fullScreen = true;
              }
              else{
                game.fullScreen = false;
              }
            }
            game.saveFile.close();
          }

	if (game.Construct(engine.ScreenWidth() * 1.5f - 46, engine.ScreenHeight() - 46, 5, 5, game.fullScreen))
		game.Start();
}