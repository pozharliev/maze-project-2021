#include "include/frontend/player.h"
#include <iostream>

//GO BIG OR GO HOME

int main()
{
    Player player;

	if (player.Construct(256, 240, 4, 4))
		player.Start();
}