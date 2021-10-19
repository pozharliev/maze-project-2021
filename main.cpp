#include "include/frontend/game.h"
#include <iostream>

//GO BIG OR GO HOME

int main()
{
	Game game;
	
	if (game.Construct(384, 216, 5, 5))
		game.Start();
}