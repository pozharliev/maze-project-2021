#include "include/frontend/player.h"
#include <iostream>

//GO BIG OR GO HOME

int main()
{
    Player player;
		if (player.Construct(384, 216, 5, 5))
			player.Start();
}