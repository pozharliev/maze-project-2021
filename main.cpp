#include "include/frontend/game.h"
#include <iostream>

//GO BIG OR GO HOME

int main()
{
	olc::PixelGameEngine engine;
	Game game;

	if (game.Construct(engine.ScreenWidth() * 1.5f - 46, engine.ScreenHeight() - 46, 5, 5))
		game.Start();
}